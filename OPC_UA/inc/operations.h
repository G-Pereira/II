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

// Indica o roller para o qual a próxima peça deve ser empurada
void pusher(uint8_t roller);

// Dá todas as informações às máquinas (faz ou não operação,	|	Parametros de entrada:
// tipo de ferramenta e tempo a atuar) para operações simples	|	celula, Unit inicial
// que devem ser executadas na peça seguinte					|	Unit final
void singleOperation(uint8_t cell, uint8_t bUnit, uint8_t fUnit);

// Atualiza a fila de ações assim que uma peça é "atuada"
void updateQueue(UA_Client * client);

// Envia para o PLC a ação da próxima peça
void updateAction(UA_Client* client);

#endif //OPERATIONS_H