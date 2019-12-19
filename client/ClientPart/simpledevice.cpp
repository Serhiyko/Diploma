#include "simpledevice.h"

SimpleLamp::SimpleLamp()
{
    m_id = 0;
    m_deviceType = DeviceType::SimpleLamp;
    m_isTurnOn = false;
}

SimpleLamp::SimpleLamp(int id)
{
    m_id = id;
    m_deviceType = DeviceType::SimpleLamp;
    m_isTurnOn = false;
}

Device* SimpleLamp::clone()
{
    return this;
}

void SimpleLamp::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("turnOn", m_isTurnOn);
}

void SimpleLamp::turnOn()
{
    m_isTurnOn = true;
}

void SimpleLamp::turnOff()
{
    m_isTurnOn = false;
}

bool SimpleLamp::isTurnOn() const
{
    return m_isTurnOn;
}

Ventilator::Ventilator()
{
    m_id = 0;
    m_deviceType = DeviceType::Ventilator;
    m_isTurnOn = false;
}

Ventilator::Ventilator(int id)
{
    m_id = id;
    m_deviceType = DeviceType::Ventilator;
    m_isTurnOn = false;
}

Device* Ventilator::clone()
{
    return this;
}

void Ventilator::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("turnOn", m_isTurnOn);
}

void Ventilator::turnOn()
{
    m_isTurnOn = true;
}

void Ventilator::turnOff()
{
    m_isTurnOn = false;
}

bool Ventilator::isTurnOn() const
{
    return m_isTurnOn;
}
