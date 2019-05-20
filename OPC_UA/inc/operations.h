#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <queue>
#include <vector>
#include "opcua.h"
using namespace std;

#define A 0
#define B 1
#define C 1

//void print_queue(void);

// Indica o roller para o qual a pr�xima pe�a deve ser empurada
void pusher(uint8_t roller);

// D� todas as informa��es �s m�quinas (faz ou n�o opera��o,	|	Parametros de entrada:
// tipo de ferramenta e tempo a atuar) para opera��es simples	|	celula, Unit inicial
// que devem ser executadas na pe�a seguinte					|	Unit final
void singleOperation(uint8_t cell, uint8_t bUnit, uint8_t fUnit);

// Atualiza a fila de a��es assim que uma pe�a � "atuada"
void updateQueue(UA_Client * client);

// Envia para o PLC a a��o da pr�xima pe�a
void updateAction(UA_Client* client);

#endif //OPERATIONS_H