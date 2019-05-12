#ifndef II_UNLOADINGORDER_H
#define II_UNLOADINGORDER_H

class UnloadingOrder : Order {
public:
	uint8_t quantity;
	uint8_t destinationPusher;
}

#endif // II_UNLOADINGORDER_H