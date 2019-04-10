#include "Factory.h"

Factory* Factory::instance = 0;

Factory* Factory::getInstance()
{
    if (instance == 0)
    {
        instance = new Factory();
    }

    return instance;
}

Factory::Factory(){

}
