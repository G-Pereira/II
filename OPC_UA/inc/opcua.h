#pragma once

#ifndef OPCUA_H
#define OPCUA_H

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

/*
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
}
*/

// Faz a liga��o com o servidor - Retorna o cliente
UA_Client* OPCUA_connect(void);

// L� uma vari�vel do tipo inteiro (retorna o seu valor)
// Recebe como par�metros de entrada o cliente e uma string com o nome da vari�vel a ler
int OPCUA_readInt(UA_Client* client, const char* var);

// Escreve uma vari�vel do tipo inteiro
// Recebe como par�metros de entrada o cliente, uma string com o nome da vari�vel e o valor a escrever
void OPCUA_writeInt(UA_Client* client, const char* var, int val);

// L� uma vari�vel do tipo boolean (retorna o seu valor)
// Recebe como par�metros de entrada o cliente e uma string com o nome da vari�vel a ler
bool OPCUA_readBool(UA_Client* client, const char* var);

// Escreve uma vari�vel do tipo boolean
// Recebe como par�metros de entrada o cliente, uma string com o nome da vari�vel e o valor a escrever
void OPCUA_writeBool(UA_Client* client, const char* var, bool val);

#endif //OPCUA_H
