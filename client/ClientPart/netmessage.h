#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#include <QDataStream>
#include <QDateTime>
#include <QString>

#include "constants.h"

class NetMessage
{
public:
    NetMessage() {}
    virtual ~NetMessage() {}

    virtual int serialize(QDataStream& pack) = 0;

    void setId(int id);

protected:
    int m_id;
};


class CreateDeviceNetMessage final : public NetMessage
{
public:
    CreateDeviceNetMessage() : NetMessage() {}

    virtual int serialize(QDataStream& pack) override;

    void setDeviceType(DeviceType type);
    void setLocationType(LocationType locationType);
    void setPosition(int posX, int posY);

private:
    DeviceType m_deviceType;
    LocationType m_locationType;
    int m_positionX;
    int m_positionY;

};

class UpdateDeviceValueNetMessage final : public NetMessage
{
public:
    UpdateDeviceValueNetMessage() : NetMessage() {}

    virtual int serialize(QDataStream& pack) override;

    void setValue(int value);

private:
    int m_value;
};

class DeleteDeviceNetMessage final : public NetMessage
{
public:
    DeleteDeviceNetMessage() : NetMessage() {}

    virtual int serialize(QDataStream& pack) override;
};

class SetDateTimeInfoMessage final : public NetMessage
{
public:
    SetDateTimeInfoMessage() : NetMessage() {}

    virtual int serialize(QDataStream& pack) override;

    void setDataTime(QDateTime dateTime);
    void setValue(int value);

private:
    QDateTime m_dateTime;
    int m_value;
};

class UpdateDevicePosition final : public NetMessage
{
public:
    UpdateDevicePosition() : NetMessage() {}

    virtual int serialize(QDataStream& pack) override;

    void setPosition(int positionX, int positionY);

private:
    int m_positionX;
    int m_positionY;
};

#endif // NETMESSAGE_H
