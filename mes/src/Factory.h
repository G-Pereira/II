#ifndef II_FACTORY_H
#define II_FACTORY_H

#include "Cell.h"
using namespace std;

class Factory {
public:
	UA_Client* client;
	queue <uint8_t> workUnit;
	queue <uint8_t> followUnit;

	vector <ProductionCell> prodCell;
	LoadingCell endCell;
	TransportationCell topCell;

	Factory(uint8_t cellID[6]);

	UA_Client* connectPLC();

	void processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit);

	void dispatchUnit(uint8_t sUnit, uint8_t objRoller);

	void updateCycle();
};

#endif