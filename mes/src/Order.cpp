#include "Order.h"

Order::Order(uint8_t ordNum, uint8_t unitType) : id(ordNum), unitType(unitType) {}

ProcessingOrder::ProcessingOrder(uint8_t ordNum, uint8_t unitType, uint8_t finalType, uint8_t quantity) : Order(ordNum, unitType), finalType(finalType), quantity(quantity) {
	this->inTime = time(NULL);
}

void ProcessingOrder::print() {
	std::cout << "ID: " << id << "\tUnit Type: " << unitType << "\tFinal Type: " << finalType << "\tQuantity: " << quantity << std::endl;
}

UnloadingOrder::UnloadingOrder(uint8_t ordNum, uint8_t unitType, uint8_t destPusher, uint8_t quantity) : Order(ordNum, unitType), destinationPusher(destPusher), quantity(quantity) {
	this->inTime = time(NULL);
}

void UnloadingOrder::print() {
	std::cout << "ID: " << id << "\tUnit Type: " << unitType << "\tDestination Pusher: " << destinationPusher << "\tQuantity: " << quantity << std::endl;	
}

