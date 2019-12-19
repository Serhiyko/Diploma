#ifndef DEVICE_H
#define DEVICE_H

#include "constants.h"
#include <QDateTime>
#include <QJsonObject>

class Device
{
public:
    virtual ~Device() {}
    virtual Device* clone() = 0;

    virtual void serialize(QJsonObject& jsonObject);

    int getId() const;

protected:
    int m_id;
    DeviceType m_deviceType;
};


#endif // DEVICE_H
