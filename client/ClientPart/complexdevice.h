#ifndef COMPLEXLAMP_H
#define COMPLEXLAMP_H

#include "device.h"

class ComplexLamp final : public Device
{
public:
    ComplexLamp();
    ComplexLamp(int id);
    ~ComplexLamp() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject &jsonObject) override;

    void setDiapasonValue(int value);
    int getDiapasonValue() const;

private:
    int m_value;
};

class Jalousie final : public Device
{
public:
    Jalousie();
    Jalousie(int id);
    ~Jalousie() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject& jsonObject) override;

    void setDiapasonValue(int value);
    int getDiapasonValue() const;

private:
    int m_value;
};

class Door final : public Device
{
public:
    Door();
    Door(int id);
    ~Door() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject& jsonObject) override;

    void setDiapasonValue(int value);
    int getDiapasonValue() const;

private:
    int m_value;
};

class Battery final : public Device
{
public:
    Battery();
    Battery(int id);
    ~Battery() {}

    virtual Device* clone() override;

    virtual void serialize(QJsonObject& jsonObject) override;

    void setDiapasonValue(int value);
    int getDiapasonValue() const;

private:
    int m_value;
};

#endif // COMPLEXLAMP_H
