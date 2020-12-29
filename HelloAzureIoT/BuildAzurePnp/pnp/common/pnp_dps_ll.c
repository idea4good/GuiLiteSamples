// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef USE_PROV_MODULE_FULL
#error "Missing cmake flag for DPS"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iothub_device_client_ll.h"
#include "iothubtransportmqtt.h"
#include "pnp_device_client_ll.h"

#include "azure_c_shared_utility/strings.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/xlogging.h"

// DPS related header files
#include "azure_prov_client/iothub_security_factory.h"
#include "azure_prov_client/prov_device_client.h"
#include "azure_prov_client/prov_transport_mqtt_client.h"
#include "azure_prov_client/prov_security_factory.h"

// Format of custom DPS payload sent when registering a PnP device.
static const char g_dps_PayloadFormatForModelId[] = "{\"modelId\":\"%s\"}";

// State of DPS registration process.  We cannot proceed with PnP until we get into the state PNP_DPS_REGISTRATION_SUCCEEDED.
typedef enum PNP_DPS_REGISTRATION_STATUS_TAG
{
    PNP_DPS_REGISTRATION_NOT_COMPLETE,
    PNP_DPS_REGISTRATION_SUCCEEDED,
    PNP_DPS_REGISTRATION_FAILED
} PNP_DPS_REGISTRATION_STATUS;

PNP_DPS_REGISTRATION_STATUS g_pnpDpsRegistrationStatus;

// Maximum amount of times we'll poll for DPS registration being ready.  Note that even though DPS works off of callbacks,
// the main() loop itself blocks 
static const int g_dpsRegistrationMaxPolls = 60;
// Amount to sleep between querying state from DPS registration loop
static const int g_dpsRegistrationPollSleep = 1000;

// IoT Hub for this device as determined by the DPS client runtime
static char* g_dpsIothubUri;
// DeviceId for this device as determined by the DPS client runtime
static char* g_dpsDeviceId;

//
// provisioningRegisterCallback is called back by the DPS client when the DPS server has either succeeded or failed our request.
//
static void provisioningRegisterCallback(PROV_DEVICE_RESULT registerResult, const char* iothubUri, const char* deviceId, void* userContext)
{
    (void)userContext;

    if (registerResult != PROV_DEVICE_RESULT_OK)
    {
        LogError("DPS Provisioning callback called with error state %d", registerResult);
        g_pnpDpsRegistrationStatus = PNP_DPS_REGISTRATION_FAILED;
    }
    else
    {
        if ((mallocAndStrcpy_s(&g_dpsIothubUri, iothubUri) != 0) ||
            (mallocAndStrcpy_s(&g_dpsDeviceId, deviceId) != 0))
        {
            LogError("Unable to copy provisioning information");
            g_pnpDpsRegistrationStatus = PNP_DPS_REGISTRATION_FAILED;
        }
        else
        {
            LogInfo("Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", iothubUri, deviceId);
            g_pnpDpsRegistrationStatus = PNP_DPS_REGISTRATION_SUCCEEDED;
        }
    }
}

IOTHUB_DEVICE_CLIENT_LL_HANDLE PnP_CreateDeviceClientLLHandle_ViaDps(const PNP_DEVICE_CONFIGURATION* pnpDeviceConfiguration)
{
    IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceHandle = NULL;
    bool result;

    PROV_DEVICE_RESULT provDeviceResult;
    PROV_DEVICE_LL_HANDLE provDeviceHandle = NULL;
    STRING_HANDLE modelIdPayload = NULL;

    LogInfo("Initiating DPS client to retrieve IoT Hub connection information");
    g_pnpDpsRegistrationStatus = PNP_DPS_REGISTRATION_NOT_COMPLETE;

    if ((modelIdPayload = STRING_construct_sprintf(g_dps_PayloadFormatForModelId, pnpDeviceConfiguration->modelId)) == NULL)
    {
        LogError("Cannot allocate DPS payload for modelId.");
        result = false;
    }
    else if ((prov_dev_set_symmetric_key_info(pnpDeviceConfiguration->u.dpsConnectionAuth.deviceId, pnpDeviceConfiguration->u.dpsConnectionAuth.deviceKey) != 0))
    {
        LogError("prov_dev_set_symmetric_key_info failed.");
        result = false;
    }
    else if (prov_dev_security_init(SECURE_DEVICE_TYPE_SYMMETRIC_KEY) != 0)
    {
        LogError("prov_dev_security_init failed");
        result = false;
    }
    else if ((provDeviceHandle = Prov_Device_LL_Create(pnpDeviceConfiguration->u.dpsConnectionAuth.endpoint, pnpDeviceConfiguration->u.dpsConnectionAuth.idScope, Prov_Device_MQTT_Protocol)) == NULL)
    {
        LogError("Failed calling Prov_Device_LL_Create");
        result = false;
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceHandle, PROV_OPTION_LOG_TRACE, &pnpDeviceConfiguration->enableTracing)) != PROV_DEVICE_RESULT_OK)
    {
        LogError("Setting provisioning tracing on failed, error=%d", provDeviceResult);
        result = false;
    }
    // This step indicates the ModelId of the device to DPS.  This allows the service to (optionally) perform custom operations,
    // such as allocating a different IoT Hub to devices based on their ModelId.
    else if ((provDeviceResult = Prov_Device_LL_Set_Provisioning_Payload(provDeviceHandle, STRING_c_str(modelIdPayload))) != PROV_DEVICE_RESULT_OK)
    {
        LogError("Failed setting provisioning data, error=%d", provDeviceResult);
        result = false;
    }
    else if ((provDeviceResult = Prov_Device_LL_Register_Device(provDeviceHandle, provisioningRegisterCallback, NULL, NULL, NULL)) != PROV_DEVICE_RESULT_OK)
    {
        LogError("Prov_Device_LL_Register_Device failed, error=%d", provDeviceResult);
        result = false;
    }
    else
    {
        for (int i = 0; (i < g_dpsRegistrationMaxPolls) && (g_pnpDpsRegistrationStatus == PNP_DPS_REGISTRATION_NOT_COMPLETE); i++)
        {
            Prov_Device_LL_DoWork(provDeviceHandle);
            ThreadAPI_Sleep(g_dpsRegistrationPollSleep);
        }

        if (g_pnpDpsRegistrationStatus == PNP_DPS_REGISTRATION_SUCCEEDED)
        {
            LogInfo("DPS successfully registered.  Continuing on to creation of IoTHub device client handle.");
            result = true;
        }
        else if (g_pnpDpsRegistrationStatus == PNP_DPS_REGISTRATION_NOT_COMPLETE)
        {
            LogError("Timed out attempting to register DPS device");
            result = false;
        }
        else
        {
            LogError("Error registering device for DPS");
            result = false;
        }
    }

    // Destroy the provisioning handle here, instead of the typical convention of doing so at the end of the function.
    // We do so because this handle is no longer required and because on devices with limited amounts of memory
    // cannot keep this open and have a device handle (via IoTHubDeviceClient_LL_CreateFromDeviceAuth below) at the same time.
    if (provDeviceHandle != NULL)
    {
        Prov_Device_LL_Destroy(provDeviceHandle);
    }

    if (result == true)
    {
        if (iothub_security_init(IOTHUB_SECURITY_TYPE_SYMMETRIC_KEY) != 0)
        {
            LogError("iothub_security_init failed");
            result = false;
        }
        else if ((deviceHandle = IoTHubDeviceClient_LL_CreateFromDeviceAuth(g_dpsIothubUri, g_dpsDeviceId, MQTT_Protocol)) == NULL)
        {
            LogError("IoTHubDeviceClient_LL_CreateFromDeviceAuth failed");
            result = true;
        }
    }

    free(g_dpsIothubUri);
    free(g_dpsDeviceId);
    STRING_delete(modelIdPayload);

    return deviceHandle;
}
