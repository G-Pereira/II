#ifndef II_UNIT_H
#define II_UNIT_H

#include <iostream>

class Unit {
public:
  uint8_t orderId;
  uint8_t destinationCellId;
  uint8_t type;

private:
};

class LoadingUnit : Unit {
public:
private:
};

class UnloadingUnit : Unit {
public:
  uint8_t destPusher;

private:
};

class ProcessingUnit : Unit {
public:
  uint8_t finalType;

private:
};

#endif // II_UNIT_H
