#include "Order.h"

Order::Order(uint8_t ordNum, uint8_t unitType, uint8_t quantity) : id(ordNum), unitType(unitType), quantity(quantity), numDoing(0), numDone(0) {}

void Order::print() {
	std::cout << "ID: " << (int)id << std::endl;
}

ProcessingOrder::ProcessingOrder(uint8_t ordNum, uint8_t unitType, uint8_t finalType, uint8_t quantity) : Order(ordNum, unitType, quantity), finalType(finalType) {}

void ProcessingOrder::print() {
	std::cout << "ID: " << (int)id << "\tUnit Type: " << (int)unitType << "\tFinal Type: " << (int)finalType << "\tQuantity: " << (int)quantity << std::endl;
}

UnloadingOrder::UnloadingOrder(uint8_t ordNum, uint8_t unitType, uint8_t destPusher, uint8_t quantity) : Order(ordNum, unitType, quantity), destinationPusher(destPusher) {}

void UnloadingOrder::print() {
	std::cout << "ID: " << (int)id << "\tUnit Type: " << (int)unitType << "\tDestination Pusher: " << (int)destinationPusher << "\tQuantity: " << (int)quantity << std::endl;	
}

