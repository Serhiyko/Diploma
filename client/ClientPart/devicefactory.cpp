#include "devicefactory.h"

#include <QtGlobal>

#include "complexdevice.h"
#include "simpledevice.h"

Device* DeviceFactory::createDevice(DeviceType type, int id)
{
    switch (type)
    {
        case DeviceType::SimpleLamp:
        {
            return (new SimpleLamp(id))->clone();
        }
        case DeviceType::ComplexLamp:
        {
            return (new ComplexLamp(id))->clone();
        }
        case DeviceType::Ventilator:
        {
            return (new Ventilator(id))->clone();
        }
        case DeviceType::Jalousie:
        {
            return (new Jalousie(id))->clone();
        }
        case DeviceType::Door:
        {
            return (new Door(id))->clone();
        }
        case DeviceType::Battery:
        {
            return (new Battery(id))->clone();
        }
        case DeviceType::None:
        {
            return nullptr;
        }
    }

    Q_ASSERT(!"Invalid DeviceType");
    return nullptr;
}

Device* DeviceFactory::createSimpleDevice(DeviceType type, int id, bool isTurnOn)
{
    switch (type)
    {
        case DeviceType::SimpleLamp:
        {
            SimpleLamp* lamp = dynamic_cast<SimpleLamp*>((new SimpleLamp(id))->clone());
            if (isTurnOn)
            {
                lamp->turnOn();
            }

            return lamp;
        }
        case DeviceType::Ventilator:
        {
            Ventilator* ventilator = dynamic_cast<Ventilator*>((new Ventilator(id))->clone());
            if (isTurnOn)
            {
                ventilator->turnOn();
            }

            return ventilator;
        }
    }

    Q_ASSERT(!"Invalid DeviceType");
    return nullptr;
}

Device* DeviceFactory::createComplexDevice(DeviceType type, int id, int value)
{
    switch (type)
    {
        case DeviceType::ComplexLamp:
        {
            ComplexLamp* lamp = dynamic_cast<ComplexLamp*>((new ComplexLamp(id))->clone());
            lamp->setDiapasonValue(value);
            return lamp;
        }
        case DeviceType::Jalousie:
        {
            Jalousie* jalousie = dynamic_cast<Jalousie*>((new Jalousie(id))->clone());
            jalousie->setDiapasonValue(value);
            return jalousie;
        }
        case DeviceType::Door:
        {
            Door* door = dynamic_cast<Door*>((new Door(id))->clone());
            door->setDiapasonValue(value);
            return door;
        }
        case DeviceType::Battery:
        {
            Battery* battery = dynamic_cast<Battery*>((new Battery(id))->clone());
            battery->setDiapasonValue(value);
            return battery;
        }
    }

    Q_ASSERT(!"Invalid DeviceType");
    return nullptr;
}
