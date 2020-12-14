#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef UA_ARCHITECTURE_PATMOS
#include <machine/patmos.h>
#include <machine/spm.h>
#include "udp.h"
#include "eth_mac_driver.h"
#endif /* UA_ARCHITECTURE_PATMOS */

#include <open62541/plugin/log_stdout.h>
#include <open62541/plugin/pubsub.h>
#include <open62541/plugin/pubsub_udp.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

#include "ua_pubsub_networkmessage.h"

#include <signal.h>

volatile _SPM int *led_ptr = (volatile _SPM int *) PATMOS_IO_LED;

UA_Boolean running = true;

char buffer_tmp[256];

__attribute__((noinline))
UA_StatusCode
subscriberListen(UA_PubSubChannel *psc) {
    //*led_ptr++;
    UA_ByteString buffer;
    UA_StatusCode retval;// = UA_ByteString_allocBuffer(&buffer, 128);

    buffer.data = buffer_tmp;
    buffer.length = 512;

    if(retval != UA_STATUSCODE_GOOD) {
        UA_LOG_ERROR(UA_Log_Stdout, UA_LOGCATEGORY_SERVER,
                     "Message buffer allocation failed!");
        return retval;
    }

    // Receive the message, non-blocking
    retval = psc->receive(psc, &buffer, NULL, 0);

    if(retval != UA_STATUSCODE_GOOD || buffer.length == 0) {
        buffer.length = 128;
        //UA_ByteString_clear(&buffer);
        memset(buffer.data, 0, buffer.length);
        return UA_STATUSCODE_GOOD;
    }

    // Decode the message 
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                "Message length: %lu", (unsigned long) buffer.length);

    UA_NetworkMessage networkMessage;
    memset(&networkMessage, 0, sizeof(UA_NetworkMessage));
    size_t currentPosition = 0;
    UA_NetworkMessage_decodeBinary(&buffer, &currentPosition, &networkMessage);
    //UA_ByteString_clear(&buffer);
    memset(buffer.data, 0, buffer.length);    

    // Is this the correct message type?
    if(networkMessage.networkMessageType != UA_NETWORKMESSAGE_DATASET)
        goto cleanup;

    // At least one DataSetMessage in the NetworkMessage?
    if(networkMessage.payloadHeaderEnabled &&
       networkMessage.payloadHeader.dataSetPayloadHeader.count < 1)
        goto cleanup;

    // Is this a KeyFrame-DataSetMessage?
    for(size_t j = 0; j < networkMessage.payloadHeader.dataSetPayloadHeader.count; j++) {
        UA_DataSetMessage *dsm = &networkMessage.payload.dataSetPayload.dataSetMessages[j];
        if(dsm->header.dataSetMessageType != UA_DATASETMESSAGE_DATAKEYFRAME)
            continue;

        // Loop over the fields and print well-known content types
        for(int i = 0; i < dsm->data.keyFrameData.fieldCount; i++) {
            const UA_DataType *currentType = dsm->data.keyFrameData.dataSetFields[i].value.type;
            if(currentType == &UA_TYPES[UA_TYPES_BYTE]) {
                UA_Byte value = *(UA_Byte *)dsm->data.keyFrameData.dataSetFields[i].value.data;
                UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                            "Message content: [Byte] \tReceived data: %i", value);
            } else if (currentType == &UA_TYPES[UA_TYPES_UINT32]) {
                UA_UInt32 value = *(UA_UInt32 *)dsm->data.keyFrameData.dataSetFields[i].value.data;
                UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                            "Message content: [UInt32] \tReceived data: %lu", value);
				//printf("Message content: [UInt32] \tReceived data: %u\n", value);
                *led_ptr = value;
				
            } else if (currentType == &UA_TYPES[UA_TYPES_DATETIME]) {
                UA_DateTime value = *(UA_DateTime *)dsm->data.keyFrameData.dataSetFields[i].value.data;
                UA_DateTimeStruct receivedTime = UA_DateTime_toStruct(value);
                UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,
                            "Message content: [DateTime] \t"
                            "Received date: %02i-%02i-%02i Received time: %02i:%02i:%02i",
                            receivedTime.year, receivedTime.month, receivedTime.day,
                            receivedTime.hour, receivedTime.min, receivedTime.sec);
            }
        }
    }

    cleanup:
    UA_NetworkMessage_clear(&networkMessage);

    return retval;
}

int main(void)
{
#ifdef UA_ARCHITECTURE_PATMOS
	static unsigned char my_ip[4] = {192, 168, 2, 1};

	eth_mac_initialize();
	arp_table_init();
	ipv4_set_my_ip(my_ip);
#endif // UA_ARCHITECTURE_PATMOS

    UA_PubSubTransportLayer udpLayer = UA_PubSubTransportLayerUDPMP();

    UA_PubSubConnectionConfig connectionConfig;
    memset(&connectionConfig, 0, sizeof(connectionConfig));
    connectionConfig.name = UA_STRING("UADP Connection 1");
    connectionConfig.transportProfileUri =
        UA_STRING("http://opcfoundation.org/UA-Profile/Transport/pubsub-udp-uadp");
    connectionConfig.enabled = UA_TRUE;

    UA_NetworkAddressUrlDataType networkAddressUrl =
        {UA_STRING_NULL , UA_STRING("opc.udp://224.0.0.22:4840/")};
    UA_Variant_setScalar(&connectionConfig.address, &networkAddressUrl,
                         &UA_TYPES[UA_TYPES_NETWORKADDRESSURLDATATYPE]);

    UA_PubSubChannel *psc = udpLayer.createPubSubChannel(&connectionConfig);
    psc->regist(psc, NULL, NULL);

    UA_StatusCode retval = UA_STATUSCODE_GOOD;/*
    while(running && retval == UA_STATUSCODE_GOOD)
        retval = subscriberListen(psc);*/
    while(1)
        subscriberListen(psc);

    psc->close(psc);


    return 0;
}