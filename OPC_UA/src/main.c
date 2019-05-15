#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <ios>
#include <fstream>
#include <stdio.h>
#include <strstream>
#include <iostream>
#include <string>
#include "open62541.h"
#pragma comment(lib, "Ws2_32.lib")
#include <signal.h>
#include <stdlib.h>

int main()
{

	UA_Client* client = UA_Client_new(UA_ClientConfig_default);

	UA_StatusCode status = UA_Client_connect(client, "opc.tcp://127.0.0.1:4840"); //opc.tcp://localhost:4840/UADiscovery

	if (status == UA_STATUSCODE_GOOD)
	{
		printf("LIGADO\n");
	}
	else printf("ERRO\n");

	UA_Variant value;
	UA_Variant_init(&value);
	UA_Variant newval;
	UA_Int16 nv = 3;

	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_INT16]);
	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN.C2T45_dt";

	//printf("the value is: %i\n", *(UA_Int32*)value.data);
	printf("vars\n");
	UA_StatusCode testnor = UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);

	printf("escrita\n");
	UA_StatusCode testnol = UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value);

	printf("leitura\n");
	if (testnol == UA_STATUSCODE_GOOD)
	{
		printf("the value is: %i\n", *(UA_Int16*)value.data);
	}
/*
	nv = 5;
	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_INT16]);

	//char str[100] = "|var|CODESYS Control Win V3 x64.Application.GVL.t2";
	//printf("the value is: %i\n", *(UA_Int32*)value.data);

	printf("vars\n");
	testnor = UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);

	printf("escrita\n");
	testnol = UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value);

	printf("leitura\n");
	if (testnol == UA_STATUSCODE_GOOD)
	{
		printf("the value is: %i\n", *(UA_Int16*)value.data);
	}
*/
	return 0;
}