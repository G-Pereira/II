#ifndef II_FACTORY_H
#define II_FACTORY_H

#include <iostream>
#include "Order.h"
#include "Cell.h"
#include "Database.h"

using namespace std;

class Factory {
public:
	UA_Client* client;
	queue <uint8_t> workUnit;
	queue <uint8_t> followUnit;
	queue <uint8_t> orderID;

	vector <uint8_t> warehouse = { 27, 27, 27, 27, 27, 27, 27, 27, 27 };

	int inputUnit, ordID;
	int unitR1, unitR2, unitR3;
	int orderR1, orderR2, orderR3, prevOrderR1 = 0, prevOrderR2 = 0, prevOrderR3 = 0;

	vector<ProcessingOrder> pOrders;
	vector<UnloadingOrder> uOrders;
	vector<bool> ordersSequence;

	vector<ProductionCell> prodCell;
	LoadingCell endCell;
	TransportationCell topCell;

	// Matrix the defines what is the top most machine that a transformation is going to use
	// First index is the initial type and second index is final type (both with an offset of one due to vectors starting at zero)
	// Used to determine availabilities of cells
	vector<vector<char>> topMachine = {
		{'0', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'},
		{'0', '0', 'B', '0', 'C', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', 'B', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', 'A', 'A', '0', 'C', 'C'},
		{'0', '0', '0', '0', 'A', 'A', '0', '0', 'C'},
		{'0', '0', '0', '0', 'A', 'A', '0', '0', '0'}
	};

	// Matrix that defines on which type of cells certain transformations can be performed
	// First index is the initial type and second index is final type (both with an offset of one due to vectors starting at zero)
	// 0 means it can be performed on any cell; 1 means it can only be performed on cells 1 and 3; 2 means it can only be perfomed on cells 2 and 4
	vector<vector<uint8_t>> possibleCells = {
		{0, 0, 1, 0, 0, 2, 0, 2, 2},
		{0, 0, 1, 0, 2, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 2, 2, 0, 2, 2},
		{0, 0, 0, 0, 2, 2, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};


	Factory(uint8_t cellID[6]);

    uint8_t recvOrders();

	bool processPOrder(ProcessingOrder* ord, uint8_t enableStacking);
	bool processUOrder(UnloadingOrder* ord);

    void pollOrders();

	UA_Client* connectPLC();

	void processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit, uint8_t orderNum);

	void dispatchUnit(uint8_t sUnit, uint8_t objRoller, uint8_t orderNum);

	void updateCycle();

private:
	void sendStorageReport();
	int8_t createXMLOrders();

	Database db;
};

#endif
