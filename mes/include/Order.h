#ifndef II_ORDER_H
#define II_ORDER_H

#include <iostream>
#include <ctime>

class Order{
public:
	uint8_t id;
	time_t inTime;
	time_t startTime;
	time_t endTime;
	uint8_t type;

	virtual void process();

private:

};

class ProcessingOrder : Order {
public:
	uint8_t quantity;
	uint8_t finalType;

  void process();
};

class UnloadingOrder : Order {
  public:
      uint8_t quantity;
      uint8_t destinationPusher;

      void process();
};

#endif //II_ORDER_H
