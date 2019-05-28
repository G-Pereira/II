#include "Order.h"

Order::Order(uint8_t ordNum, uint8_t unitType) : id(ordNum), unitType(unitType) {}

uint8_t Order::process() {}

void Order::print() {
	std::cout << "ID: " << (int)id << std::endl;
}

ProcessingOrder::ProcessingOrder(uint8_t ordNum, uint8_t unitType, uint8_t finalType, uint8_t quantity) : Order(ordNum, unitType), finalType(finalType), quantity(quantity) {
	this->inTime = time(NULL);
}

uint8_t ProcessingOrder::process(Factory *fac, bool enableStacking) {		// TODO: don't send when there aren't enough units // TODO: check if it is a possible order
	Cell *cell;
	uint8_t possCell = possibleCells[unitType][finalType];
	char topMach = topMachine[unitType][finalType];
	uint8_t minAvailability = 9;
	uint8_t minCell;

	for(int i = possCell%2; i < 4; i += possCell/2) {
		cell = fac->prodCell[i];

		switch(topMach) {
		case 'A':
			if(cellAvailability[i] < 3+enableStacking && cellAvailability[i] < minAvailability) {
				minCell = i;
				minAvailability = cellAvailability[i];
			}
			break;

		case 'B':
			if(cellAvailability[i] < 2+2*enableStacking && cellAvailability[i] < minAvailability) {
				minCell = i;
				minAvailability = cellAvailability[i];
			}
			break;

		case 'C':
			if(cellAvailability[i] < 1+3*enableStacking && cellAvailability[i] < minAvailability) {
				minCell = i;
				minAvailability = cellAvailability[i];
			}
			break;
		}
	}
	
	if(minAvailability < 9) {
		// TODO: change quantities on order class

		switch(minCell) {		// TODO: lower availabilities
		case 0: case 2:
			if(minAvailability > 1) fac->prodCell[minCell].generalAvailability++;
			else if(topMach == 'A') fac->prodCell[minCell].generalAvailability = 4;
			else fac->prodCell[minCell].generalAvailability++;
			break;

		case 1: case 3:
			if(minAvailability == 0 && topMach == 'A') fac->prodCell[minCell].generalAvailability = 2;
			else fac->prodCell[minCell].generalAvailability++;
			break;
		}

		fac->processUnit(minCell, unitType, finalType);

		return 1;
	}
}

void ProcessingOrder::print() {
	std::cout << "ID: " << (int)id << "\tUnit Type: " << (int)unitType << "\tFinal Type: " << (int)finalType << "\tQuantity: " << (int)quantity << std::endl;
}

UnloadingOrder::UnloadingOrder(uint8_t ordNum, uint8_t unitType, uint8_t destPusher, uint8_t quantity) : Order(ordNum, unitType), destinationPusher(destPusher), quantity(quantity) {
	this->inTime = time(NULL);
}

uint8_t UnloadingOrder::process() {		// TODO
	return 0;
}

void UnloadingOrder::print() {
	std::cout << "ID: " << (int)id << "\tUnit Type: " << (int)unitType << "\tDestination Pusher: " << (int)destinationPusher << "\tQuantity: " << (int)quantity << std::endl;	
}

