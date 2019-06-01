#include "opcua.h"

// Faz a ligação com o servidor - Retorna o cliente
UA_Client* OPCUA_connect(void) {

	UA_Client* client = UA_Client_new(UA_ClientConfig_default);
	UA_StatusCode status = UA_Client_connect(client, "opc.tcp://127.0.0.1:4840");

	if (status != UA_STATUSCODE_GOOD) printf("ERRO\n");

	return client;
}

// Lê uma variável do tipo inteiro (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
int OPCUA_readInt(UA_Client * client, const char* var) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant value;			//declaração da 
	UA_Variant_init(&value);	//variável value
	while (UA_STATUSCODE_GOOD != UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value)); // Guarda em "value" o valor da variável "var" 

	return *(UA_Int16*)value.data;
}

// Escreve uma variável do tipo inteiro
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeInt(UA_Client * client, const char* var, int val) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant newval;
	UA_Int16 nv = val;
	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_INT16]);
	while (UA_STATUSCODE_GOOD != UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval));
}

// Lê uma variável do tipo boolean (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
bool OPCUA_readBool(UA_Client * client, const char* var) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant value;			//declaração da 
	UA_Variant_init(&value);	//variável value
	UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, str), &value); // Guarda em "value" o valor da variável "var" 

	return *(UA_Boolean*)value.data;
}

// Escreve uma variável do tipo boolean
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeBool(UA_Client * client, const char* var, bool val) {

	char str[100] = "|var|CODESYS Control Win V3 x64.Application.MAIN."; // Mapeamento da variável "var"
	strcat_s(str, var);

	UA_Variant newval;
	UA_Boolean nv = val;
	UA_Variant_setScalar(&newval, &nv, &UA_TYPES[UA_TYPES_BOOLEAN]);
	UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, str), &newval);
}













