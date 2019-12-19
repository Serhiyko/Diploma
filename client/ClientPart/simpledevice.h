#ifndef SIMPLELAMP_H
#define SIMPLELAMP_H

#include "device.h"

class SimpleLamp final : public Device
{
public:
    SimpleLamp();
    SimpleLamp(int id);
    ~SimpleLamp() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject& jsonObject) override;

    void turnOn();
    void turnOff();
    bool isTurnOn() const;

private:
    bool m_isTurnOn;
};

class Ventilator : public Device
{
public:
    Ventilator();
    Ventilator(int id);
    ~Ventilator() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject& jsonObject) override;

    void turnOn();
    void turnOff();
    bool isTurnOn() const;

private:
    bool m_isTurnOn;
};

#endif // SIMPLELAMP_H
