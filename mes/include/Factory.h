#ifndef II_FACTORY_H
#define II_FACTORY_H

#include <iostream>
#include "Order.h"
#include "Cell.h"
using namespace std;

class Factory {
public:
	UA_Client* client;
	queue <uint8_t> workUnit;
	queue <uint8_t> followUnit;

	vector<ProcessingOrder*> pOrders;
	vector<UnloadingOrder*> uOrders;
	vector<bool> ordersSequence;

	vector<ProductionCell> prodCell;
	LoadingCell endCell;
	TransportationCell topCell;

	// Matrix the defines what is the top most machine that a transformation is going to use
	// First index is the initial type and second index is final type (both with an offset of one due to vectors starting at zero)
	// Used to determine availabilities of cells
	vector<vector<char>> topMachine = {		// TODO: availability should change differently for AA transformation
		{'0', 'A', 'A', 'A', 'A', '0', 'A', 'A', '0'},
		{'0', '0', 'B', '0', 'C', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', 'B', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', 'A', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
		{'0', '0', '0', '0', '0', '0', '0', 'C', 'C'},
		{'0', '0', '0', '0', 'A', '0', '0', '0', 'C'},
		{'0', '0', '0', '0', 'A', 'A', '0', '0', '0'}
	};

	// Matrix that defines on which type of cells certain transformations can be performed
	// First index is the initial type and second index is final type (both with an offset of one due to vectors starting at zero)
	// 0 means it can be performed on any cell; 1 means it can only be performed on cells 1 and 3; 2 means it can only be perfomed on cells 2 and 4
	vector<vector<uint8_t>> possibleCells = {		// TODO
		{0, 0, 1, 0, 1, 0, 0, 2, 0},
		{0, 0, 1, 0, 2, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 2, 0},
		{0, 0, 0, 0, 2, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 1, 0, 0, 0}
	};


	Factory(uint8_t cellID[6]);

    uint8_t recvOrders();

	bool processPOrder(ProcessingOrder* ord, uint8_t enableStacking);
	bool processUOrder(UnloadingOrder* ord);

    void pollOrders();

	UA_Client* connectPLC();

	void processUnit(uint8_t cell, uint8_t bUnit, uint8_t fUnit);

	void dispatchUnit(uint8_t sUnit, uint8_t objRoller);

	void updateCycle();

private:
	int8_t recvOrdersFile();
	int8_t createXMLOrders();
};

#endif