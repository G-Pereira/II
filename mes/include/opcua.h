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

// Faz a ligação com o servidor - Retorna o cliente
UA_Client* OPCUA_connect(void);

// Lê uma variável do tipo inteiro (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
int OPCUA_readInt(UA_Client* client, const char* var);

// Escreve uma variável do tipo inteiro
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeInt(UA_Client* client, const char* var, int val);

// Lê uma variável do tipo boolean (retorna o seu valor)
// Recebe como parâmetros de entrada o cliente e uma string com o nome da variável a ler
bool OPCUA_readBool(UA_Client* client, const char* var);

// Escreve uma variável do tipo boolean
// Recebe como parâmetros de entrada o cliente, uma string com o nome da variável e o valor a escrever
void OPCUA_writeBool(UA_Client* client, const char* var, bool val);

#endif //OPCUA_H
