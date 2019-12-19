#include "device.h"

void Device::serialize(QJsonObject& jsonObject)
{
    jsonObject.insert("device_type", static_cast<int>(m_deviceType));
    jsonObject.insert("id", m_id);
}

int Device::getId() const
{
    return m_id;
}
