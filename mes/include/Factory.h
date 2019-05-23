#include <iostream>
#include <queue>
#include <vector>
#include "Cell.h"
#include "opcua.h"
using namespace std;

class Factory {
public:
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
