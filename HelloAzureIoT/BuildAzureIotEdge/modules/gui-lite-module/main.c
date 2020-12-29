// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "iothub_module_client_ll.h"
#include "iothub_client_options.h"
#include "iothub_message.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/shared_util_options.h"
#include "iothubtransportmqtt.h"
#include "iothub.h"
#include "time.h"

typedef struct MESSAGE_INSTANCE_TAG
{
    IOTHUB_MESSAGE_HANDLE messageHandle;
    size_t messageTrackingId;  // For tracking the messages within the user callback.
} 
MESSAGE_INSTANCE;

size_t messagesReceivedByInput1Queue = 0;

// SendConfirmationCallback is invoked when the message that was forwarded on from 'InputQueue1Callback'
// pipeline function is confirmed.
static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    // The context corresponds to which message# we were at when we sent.
    MESSAGE_INSTANCE* messageInstance = (MESSAGE_INSTANCE*)userContextCallback;
    printf("Confirmation[%zu] received for message with result = %d\r\n", messageInstance->messageTrackingId, result);
    IoTHubMessage_Destroy(messageInstance->messageHandle);
    free(messageInstance);
}

// Allocates a context for callback and clones the message
// NOTE: The message MUST be cloned at this stage.  InputQueue1Callback's caller always frees the message
// so we need to pass down a new copy.
static MESSAGE_INSTANCE* CreateMessageInstance(IOTHUB_MESSAGE_HANDLE message)
{
    MESSAGE_INSTANCE* messageInstance = (MESSAGE_INSTANCE*)malloc(sizeof(MESSAGE_INSTANCE));
    if (NULL == messageInstance)
    {
        printf("Failed allocating 'MESSAGE_INSTANCE' for pipelined message\r\n");
    }
    else
    {
        memset(messageInstance, 0, sizeof(*messageInstance));

        if ((messageInstance->messageHandle = IoTHubMessage_Clone(message)) == NULL)
        {
            free(messageInstance);
            messageInstance = NULL;
        }
        else
        {
            messageInstance->messageTrackingId = messagesReceivedByInput1Queue;
        }
    }

    return messageInstance;
}

static IOTHUBMESSAGE_DISPOSITION_RESULT InputQueue1Callback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    IOTHUB_CLIENT_RESULT clientResult;
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle = (IOTHUB_MODULE_CLIENT_LL_HANDLE)userContextCallback;

    unsigned const char* messageBody;
    size_t contentSize;

    if (IoTHubMessage_GetByteArray(message, &messageBody, &contentSize) != IOTHUB_MESSAGE_OK)
    {
        messageBody = "<null>";
    }

    printf("Received Message [%zu]\r\n Data: [%s]\r\n", 
            messagesReceivedByInput1Queue, messageBody);

    // This message should be sent to next stop in the pipeline, namely "output1".  What happens at "outpu1" is determined
    // by the configuration of the Edge routing table setup.
    MESSAGE_INSTANCE *messageInstance = CreateMessageInstance(message);
    if (NULL == messageInstance)
    {
        result = IOTHUBMESSAGE_ABANDONED;
    }
    else
    {
        printf("Sending message (%zu) to the next stage in pipeline\n", messagesReceivedByInput1Queue);

        clientResult = IoTHubModuleClient_LL_SendEventToOutputAsync(iotHubModuleClientHandle, messageInstance->messageHandle, "output1", SendConfirmationCallback, (void *)messageInstance);
        if (clientResult != IOTHUB_CLIENT_OK)
        {
            IoTHubMessage_Destroy(messageInstance->messageHandle);
            free(messageInstance);
            printf("IoTHubModuleClient_LL_SendEventToOutputAsync failed on sending msg#=%zu, err=%d\n", messagesReceivedByInput1Queue, clientResult);
            result = IOTHUBMESSAGE_ABANDONED;
        }
        else
        {
            result = IOTHUBMESSAGE_ACCEPTED;
        }
    }

    messagesReceivedByInput1Queue++;
    return result;
}

static IOTHUB_MODULE_CLIENT_LL_HANDLE InitializeConnection()
{
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle;

    if (IoTHub_Init() != 0)
    {
        printf("Failed to initialize the platform.\r\n");
        iotHubModuleClientHandle = NULL;
    }
    else if ((iotHubModuleClientHandle = IoTHubModuleClient_LL_CreateFromEnvironment(MQTT_Protocol)) == NULL)
    {
        printf("ERROR: IoTHubModuleClient_LL_CreateFromEnvironment failed\r\n");
    }
    else
    {
        // Uncomment the following lines to enable verbose logging.
        // bool traceOn = true;
        // IoTHubModuleClient_LL_SetOption(iotHubModuleClientHandle, OPTION_LOG_TRACE, &trace);
    }

    return iotHubModuleClientHandle;
}

static void DeInitializeConnection(IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle)
{
    if (iotHubModuleClientHandle != NULL)
    {
        IoTHubModuleClient_LL_Destroy(iotHubModuleClientHandle);
    }
    IoTHub_Deinit();
}

static int SetupCallbacksForModule(IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle)
{
    int ret;

    if (IoTHubModuleClient_LL_SetInputMessageCallback(iotHubModuleClientHandle, "input1", InputQueue1Callback, (void*)iotHubModuleClientHandle) != IOTHUB_CLIENT_OK)
    {
        printf("ERROR: IoTHubModuleClient_LL_SetInputMessageCallback(\"input1\")..........FAILED!\r\n");
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

void module_connection_status_callback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* userContextCallback)
{
	if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
	{
        printf("GuiLite connected to iothub ✔️\r\n");
	}
	else
	{
        printf("GuiLite disconnected ❌\r\n");
	}
    fflush(stdout);
}

extern char* getCurrentUtcTime();
extern char* getDeviceInfo();
void handle_unknow_method(const char* method_name, const unsigned char* payload, size_t size, unsigned char** response, size_t* response_size)
{
    int static count;
    printf("get method request: name = %s, payload= %s, size = %lu 🔔 X %d\r\n", method_name, payload, size, ++count);
    fflush(stdout);

    *response = calloc(1, (1024 * 2));
    sprintf(*response, "{ \"Your method\" : \"%s\", \"Your payload\" : '%s', \"Timestamp\" : \"%s\", \"Device info\" : \"%s\" }", method_name, payload, getCurrentUtcTime(), getDeviceInfo());// If payload contain doule quotation, do not use double quotation like: \"payload\" : "%s", use single quotation instead.
    *response_size = strlen(*response);
}

int module_method_callback(const char* method_name, const unsigned char* payload, size_t size, unsigned char** response, size_t* response_size, void* userContextCallback)
{
    handle_unknow_method(method_name, payload, size, response, response_size);
    return 200;
}

void iothub_module()
{
    IOTHUB_MODULE_CLIENT_LL_HANDLE iotHubModuleClientHandle;

    srand((unsigned int)time(NULL));

    if ((iotHubModuleClientHandle = InitializeConnection()) != NULL && SetupCallbacksForModule(iotHubModuleClientHandle) == 0)
    {
        if(IOTHUB_CLIENT_OK != IoTHubModuleClient_LL_SetConnectionStatusCallback(iotHubModuleClientHandle, module_connection_status_callback, iotHubModuleClientHandle))
        {
            printf("SetConnectionStatusCallback failed ❌\r\n");
        }
        else
        {
            printf("SetConnectionStatusCallback done ✔️\r\n");
        }
        fflush(stdout);

        if(IOTHUB_CLIENT_OK != IoTHubModuleClient_LL_SetModuleMethodCallback(iotHubModuleClientHandle, module_method_callback, iotHubModuleClientHandle))
        {
            printf("SetModuleMethodCallback failed ❌\r\n");
        }
        else
        {
            printf("SetModuleMethodCallback done ✔️\r\n");
        }

        while (true)
        {
            IoTHubModuleClient_LL_DoWork(iotHubModuleClientHandle);
            ThreadAPI_Sleep(100);
        }
    }

    DeInitializeConnection(iotHubModuleClientHandle);
}

int main(void)
{
    printf("GuiLite start\n");
    fflush(stdout);

    iothub_module();

    printf("GuiLite end\n");
    fflush(stdout);
    return 0;
}
