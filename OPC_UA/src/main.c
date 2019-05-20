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

// Faz a ligação com o servidor - Retorna o cliente
UA_Client* OPCUA_connect(void) {
	
	UA_Client* client = UA_Client_new(UA_ClientConfig_default);
	UA_StatusCode status = UA_Client_connect(client, "opc.tcp://127.0.0.1:4840");

	if (status != UA_STATUSCODE_GOOD) printf("ERRO\n");

	return client;
}

// Lê uma variável do tipo inteiro (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
int OPCUA_readInt(UA_Client* client, const char *var) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant value;			//declaração da 
	UA_Variant_init(&value);	//variável value
	UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value); // Guarda em "value" o valor da variável "var" 
	
	return *(UA_Int16*)value.data;
}

// Escreve uma variável do tipo inteiro
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeInt(UA_Client* client, const char* var, int val) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant newval;
	UA_Int16 nv = val;
	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_INT16]);
	UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);
}

// Lê uma variável do tipo boolean (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
bool OPCUA_readBool(UA_Client* client, const char* var) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant value;			//declaração da 
	UA_Variant_init(&value);	//variável value
	UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value); // Guarda em "value" o valor da variável "var" 

	return *(UA_Boolean*)value.data;
}

// Escreve uma variável do tipo boolean
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeBool(UA_Client* client, const char* var, bool val) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant newval;
	UA_Boolean nv = val;
	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_BOOLEAN]);
	UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);
}

int main()
{
	UA_Client* client = OPCUA_connect();

	// Write int
	OPCUA_writeInt(client, "C2T45_dt", 2);

	// Read int
	int val = OPCUA_readInt(client, "C2T45_dt");
	printf("the value is: %i\n", val);

	// Write bool
	OPCUA_writeBool(client, "C2T2_f", true);

	// Read bool
	bool valB = OPCUA_readBool(client, "C2T2_f");
	printf("the value is: %i\n", valB);

	return 0;

	/*
		UA_StatusCode testnor = UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);
		if (testnol == UA_STATUSCODE_GOOD) printf("the value is: %i\n", *(UA_Int16*)value.data);
	*/
}