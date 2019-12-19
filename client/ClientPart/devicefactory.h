#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "device.h"
#include "constants.h"

class DeviceFactory
{
public:
    DeviceFactory() {}
    ~DeviceFactory() {}

    Device* createDevice(DeviceType type, int id);
    Device* createSimpleDevice(DeviceType type, int id, bool isTurnOn);
    Device* createComplexDevice(DeviceType type, int id, int value);
};

#endif // DEVICEFACTORY_H
