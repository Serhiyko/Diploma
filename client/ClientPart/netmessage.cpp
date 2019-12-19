#include "netmessage.h"
#include "netobject.h"

void NetMessage::setId(int id)
{
    m_id = id;
}

int CreateDeviceNetMessage::serialize(QDataStream& pack)
{
    pack << static_cast<int>(MessageType::CreateDevice);
    pack << static_cast<int>(m_deviceType);
    pack << m_id;
    pack << NetObject::getInstance().getUserId();
    pack << static_cast<int>(m_locationType);
    pack << m_positionX;
    pack << m_positionY;

    return sizeof(pack);
}

void CreateDeviceNetMessage::setDeviceType(DeviceType type)
{
    m_deviceType = type;
}

void CreateDeviceNetMessage::setLocationType(LocationType locationType)
{
    m_locationType = locationType;
}

void CreateDeviceNetMessage::setPosition(int positionX, int positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
}

int UpdateDeviceValueNetMessage::serialize(QDataStream& pack)
{
    pack << static_cast<int>(MessageType::UpdateDeviceStatus);
    pack << m_id;
    pack << NetObject::getInstance().getUserId();
    pack << m_value;

    return sizeof(pack);
}

void UpdateDeviceValueNetMessage::setValue(int value)
{
    m_value = value;
}

int DeleteDeviceNetMessage::serialize(QDataStream& pack)
{
    pack << static_cast<int>(MessageType::DeleteDevice);
    pack << m_id;
    pack << NetObject::getInstance().getUserId();

    return sizeof(pack);
}

int SetDateTimeInfoMessage::serialize(QDataStream& pack)
{
    pack << static_cast<int>(MessageType::SetDateTimeEvent);
    pack << m_id;
    pack << NetObject::getInstance().getUserId();
    pack << m_value;
    QString dateTime = m_dateTime.date().toString("dd.MM.yyyy") + "T" + m_dateTime.time().toString("HH:mm:ss");
    pack.writeRawData(dateTime.toStdString().c_str(), dateTime.length());

    return sizeof(pack);
}

void SetDateTimeInfoMessage::setDataTime(QDateTime dateTime)
{
    m_dateTime = dateTime;
}

void SetDateTimeInfoMessage::setValue(int value)
{
    m_value = value;
}

int UpdateDevicePosition::serialize(QDataStream& pack)
{
    pack << static_cast<int>(MessageType::UpdateDevicePosition);
    pack << m_id;
    pack << NetObject::getInstance().getUserId();
    pack << m_positionX;
    pack << m_positionY;

    return sizeof(pack);
}

void UpdateDevicePosition::setPosition(int positionX, int positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
}
