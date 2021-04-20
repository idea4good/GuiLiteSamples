#include <unistd.h>
#include <pthread.h>
#include "iothub.h"
#include "iothub_device_client_ll.h"
#include "iothub_client_options.h"
#include "azure_c_shared_utility/xlogging.h"
#include "pnp_dps_ll.h"
#include "parson/parson.h"

#define USING_CONNECTION_STRING
#ifdef USING_CONNECTION_STRING
static const char* s_ConnectionString = "HostName=____________________.azure-devices.net;DeviceId=__________;SharedAccessKey=V1AOYFQGp9Sf8XB5U0o1gC/9kMNQDQXauMXQRi6rZvQ=";
#endif

static const PNP_DEVICE_CONFIGURATION s_Configuration = {
    // Config from Device Provision Service:
    .u.dpsConnectionAuth.idScope = "0ne001E32DA",// from DPS ID Scope,
    .u.dpsConnectionAuth.deviceId = "enroll-individual-pnp-gui-lite",//from DPS individual enrollment/REGISTRATION ID,
    .u.dpsConnectionAuth.deviceKey = "hhDtFCmr311gPIsjUY1OKGdV8zXo053iu35MQutW2HQG+VSlW12mwYX4uvSwffxUGEXejITaTOkcst2lOOBkog==",// from DPS individual enrollment primary key,

    // Do not need change:
    .u.dpsConnectionAuth.endpoint = "global.azure-devices-provisioning.net",
    .securityType = PNP_CONNECTION_SECURITY_TYPE_DPS,
    .modelId = "dtmi:AzureDeviceUpdate;1",
    .enableTracing = true
};

extern char* getCurrentUtcTime();
extern char* getDeviceInfo();
static void HandleUnknowMethod(const char* methodName, const unsigned char* payload, size_t size, unsigned char** response, size_t* responseSize)
{
    int static count;
    LogInfo("Get method request: name = %s, payload= %s, size = %lu 🔔 X %d", methodName, payload, size, ++count);

    *response = calloc(1, (1024 * 2));
    sprintf(*response, "{ \"Your method\" : \"%s\", \"Timestamp\" : \"%s\", \"Device info\" : \"%s\" }", methodName, getCurrentUtcTime(), getDeviceInfo());// payload has bad format, could not be recognized
    *responseSize = strlen(*response);
}

static int DeviceMethodCallback(const char* methodName, const unsigned char* payload, size_t size, unsigned char** response, size_t* responseSize, void* userContextCallback)
{
    HandleUnknowMethod(methodName, payload, size, response, responseSize);
    return 200;
}

static void SendReportToDeviceTwin(IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceClientLL, const char* pay_laod)
{
    IOTHUB_CLIENT_RESULT iothubClientResult;
    if ((iothubClientResult = IoTHubDeviceClient_LL_SendReportedState(deviceClientLL, (const unsigned char*)pay_laod, strlen(pay_laod), NULL, NULL)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to send reported state, error = %d", iothubClientResult);
        return;
    }
    LogInfo("Report sent ✔️");
}

static void DeviceTwinCallback(DEVICE_TWIN_UPDATE_STATE updateState, const unsigned char* payload, size_t size, void* userContextCallback)
{
    IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceClientLL = (IOTHUB_DEVICE_CLIENT_LL_HANDLE)userContextCallback;
    LogInfo("🌏 Get device twin request: state = %d, payload = %s, size = %lu", updateState, payload, size);
    
    const char deviceInfo[] = "{\"deviceInformation\":{\"__t\":\"c\",\"manufacturer\":\"UnknownMFR\",\"model\":\"UnknownModel\",\"osName\":\"Linux\",\"swVersion\":\"2020.109.116.117\",\"processorArchitecture\":\"x86-64\",\"processorManufacturer\":\"GenuineIntel\",\"totalMemory\":13032812,\"totalStorage\":263174212}}";
    SendReportToDeviceTwin(deviceClientLL, deviceInfo);

    const char aduInfo[] = "{\"azureDeviceUpdateAgent\":{\"__t\":\"c\",\"client\":{\"state\":0,\"resultCode\":200,\"extendedResultCode\":0,\"deviceProperties\":{\"manufacturer\":\"Microsoft\",\"model\":\"Azure-Percept-DK\"}}}}";
    SendReportToDeviceTwin(deviceClientLL, aduInfo);
}

void SendTelemetry(IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceClientLL) 
{
    IOTHUB_MESSAGE_HANDLE messageHandle = NULL;
    IOTHUB_CLIENT_RESULT iothubResult;

    if ((messageHandle = IoTHubMessage_CreateFromString("{\"temperature\":22.00}")) == NULL)
    {
        LogError("IoTHubMessage_CreateFromString failed");
    }
    else if ((iothubResult = IoTHubDeviceClient_LL_SendEventAsync(deviceClientLL, messageHandle, NULL, NULL)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to send telemetry message, error = %d", iothubResult);
    }
    LogInfo("Telemetry sent ✔️");
    IoTHubMessage_Destroy(messageHandle);
}

extern const TRANSPORT_PROVIDER* MQTT_Protocol(void);
static IOTHUB_DEVICE_CLIENT_LL_HANDLE CreateAndConfigureDeviceClientHandleForPnP(void)
{
    IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceHandle = NULL;
    IOTHUB_CLIENT_RESULT iothubResult;
    bool urlAutoEncodeDecode = true;
    int iothubInitResult;

    if ((iothubInitResult = IoTHub_Init()) != 0)
    {
        LogError("Failure to initialize client, error=%d", iothubInitResult);
    }
#ifdef USING_CONNECTION_STRING
    else if ((deviceHandle = IoTHubDeviceClient_LL_CreateFromConnectionString(s_ConnectionString, MQTT_Protocol)) == NULL)
    {
        LogError("Failure creating IotHub client.  Hint: Check your connection string or DPS configuration");
    }
#else
    else if ((deviceHandle = PnP_CreateDeviceClientLLHandle_ViaDps(&s_Configuration)) == NULL)
    {
        LogError("Failure creating IotHub client.  Hint: Check your connection string or DPS configuration");
    }
#endif
    else if ((iothubResult = IoTHubDeviceClient_LL_SetOption(deviceHandle, OPTION_MODEL_ID, s_Configuration.modelId)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to set the ModelID, error=%d", iothubResult);
    }
    else if ((iothubResult = IoTHubDeviceClient_LL_SetDeviceMethodCallback(deviceHandle, DeviceMethodCallback, NULL)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to set device method callback, error=%d", iothubResult);
    }
    else if ((iothubResult = IoTHubDeviceClient_LL_SetDeviceTwinCallback(deviceHandle, DeviceTwinCallback, (void*)deviceHandle)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to set device twin callback, error=%d", iothubResult);
    }
    // Enabling auto url encode will have the underlying SDK perform URL encoding operations automatically.
    else if ((iothubResult = IoTHubDeviceClient_LL_SetOption(deviceHandle, OPTION_AUTO_URL_ENCODE_DECODE, &urlAutoEncodeDecode)) != IOTHUB_CLIENT_OK)
    {
        LogError("Unable to set auto Url encode option, error=%d", iothubResult);
    }
    else
    {
        return deviceHandle;
    }

    IoTHub_Deinit();
    IoTHubDeviceClient_LL_Destroy(deviceHandle);
    return NULL;
}

void* telemetryRoutine(void* param)
{
    while (true)
    {
        SendTelemetry((IOTHUB_DEVICE_CLIENT_LL_HANDLE)param);
        sleep(60);
    }
}

int main(void)
{
    IOTHUB_DEVICE_CLIENT_LL_HANDLE deviceClientLL = NULL;
    if ((deviceClientLL = CreateAndConfigureDeviceClientHandleForPnP()) == NULL)
    {
        LogError("Creating IotHub device client failed");
        return -1;
    }
    
    while (true)
    {
        IoTHubDeviceClient_LL_DoWork(deviceClientLL);
        usleep(100000);
    }

    IoTHubDeviceClient_LL_Destroy(deviceClientLL);
    IoTHub_Deinit();
    return 0;
}
