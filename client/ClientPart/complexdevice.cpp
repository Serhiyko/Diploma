#include "complexdevice.h"

ComplexLamp::ComplexLamp()
{
    m_id = 0;
    m_deviceType = DeviceType::ComplexLamp;
    m_value = 0;
}

ComplexLamp::ComplexLamp(int id)
{
    m_id = id;
    m_deviceType = DeviceType::ComplexLamp;
    m_value = 0;
}

Device* ComplexLamp::clone()
{
    return this;
}

void ComplexLamp::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("value", m_value);
}

void ComplexLamp::setDiapasonValue(int value)
{
    m_value = value;
}

int ComplexLamp::getDiapasonValue() const
{
    return m_value;
}

Jalousie::Jalousie()
{
    m_id = 0;
    m_deviceType = DeviceType::Jalousie;
    m_value = 0;
}

Jalousie::Jalousie(int id)
{
    m_id = id;
    m_deviceType = DeviceType::Jalousie;
    m_value = 0;
}

Device* Jalousie::clone()
{
    return this;
}

void Jalousie::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("value", m_value);
}

void Jalousie::setDiapasonValue(int value)
{
    m_value = value;
}

int Jalousie::getDiapasonValue() const
{
    return m_value;
}

Door::Door()
{
    m_id = 0;
    m_deviceType = DeviceType::Door;
    m_value = 0;
}

Door::Door(int id)
{
    m_id = id;
    m_deviceType = DeviceType::Door;
    m_value = 0;
}

Device* Door::clone()
{
    return this;
}

void Door::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("value", m_value);
}

void Door::setDiapasonValue(int value)
{
    m_value = value;
}

int Door::getDiapasonValue() const
{
    return m_value;
}

Battery::Battery()
{
    m_id = 0;
    m_deviceType = DeviceType::Battery;
    m_value = 0;
}

Battery::Battery(int id)
{
    m_id = id;
    m_deviceType = DeviceType::Battery;
    m_value = 0;
}

Device* Battery::clone()
{
    return this;
}

void Battery::serialize(QJsonObject& jsonObject)
{
    Device::serialize(jsonObject);
    jsonObject.insert("value", m_value);
}

void Battery::setDiapasonValue(int value)
{
    m_value = value;
}

int Battery::getDiapasonValue() const
{
    return m_value;
}
