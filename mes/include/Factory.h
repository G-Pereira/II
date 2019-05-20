#ifndef II_FACTORY_H
#define II_FACTORY_H

#include <vector>
#include <iostream>
#include <string>

class Factory {
public:
    static Factory* getInstance();
    uint8_t recvOrders();
    void pollOrders();

private:
    static Factory* instance;
    Factory();
    std::vector<uint8_t> numUnits;

};


#endif //II_FACTORY_H
