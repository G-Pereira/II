#ifndef II_FACTORY_H
#define II_FACTORY_H

#include "Cell.h"
using namespace std;

class Factory {
public:
	UA_Client* client;
	queue <int> unit;

	ProductionCell cell1;
	ProductionCell cell2;
	ProductionCell cell3;
	ProductionCell cell4;

	LoadingCell endCell;

	TransportationCell topCell;

	Factory(uint8_t cellID[6]);

	UA_Client* connectPLC();
};

#endif