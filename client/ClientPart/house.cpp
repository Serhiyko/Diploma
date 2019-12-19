#include "house.h"

#include "constants.h"
#include "complexdevice.h"
#include "netobject.h"
#include "netmessage.h"
#include "simpledevice.h"

#include <QDebug>
#include <QPointer>
#include <QByteArray>
#include <QDataStream>

House& House::getInstance()
{
    static House* instance = new House();
    return *instance;
}

House::House()
{
    m_id = 0;
    m_jsonManager = new JsonManager();
    m_deviceFactory = new DeviceFactory();
}

House::~House()
{
    m_model.clear();
    m_devices.clear();

    delete m_deviceFactory;
    delete m_jsonManager;
}

void House::createDevices(DeviceType type, QWidget* widget)
{
    updateId();

    Device* device = m_deviceFactory->createDevice(type, m_id);
    m_devices.insert(type, device);

    Model* model = new Model(type, device, widget);
    sendMessageAboutDeviceCreation(type, *model);

    m_model.push_back(model);

    m_jsonManager->write(m_devices, m_model);
}

void House::updateId(int value)
{
    m_id = (value == 0) ? (m_id + 1) : value;
}

void House::sendMessageAboutDeviceCreation(DeviceType type, const Model& model)
{
    CreateDeviceNetMessage* msg = new CreateDeviceNetMessage();
    msg->setDeviceType(type);
    msg->setId(m_id);
    msg->setLocationType(model.getLocationType());
    msg->setPosition(model.getX(), model.getY());

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);

    NetObject::getInstance().registerMessage(MessageType::CreateDevice, m_id);
    NetObject::getInstance().sendMessage(data);

    delete msg;
}

void House::createSimpleDevice(QWidget* locationWidget,
                               const std::tuple<int, int, int, int, bool>& parameters)
{
    int deviceTypeId = std::get<3>(parameters);
    int deviceId = std::get<2>(parameters);
    bool isTurnOn = std::get<4>(parameters);

    DeviceType type = static_cast<DeviceType>(deviceTypeId);
    Device* device = m_deviceFactory->createSimpleDevice(type, deviceId, isTurnOn);
    m_devices.insert(type, device);

    int positionX = std::get<0>(parameters);
    int positionY = std::get<1>(parameters);

    Model* model = new Model(type, device, locationWidget, positionX, positionY);
    m_model.push_back(model);

    setId(deviceId);
}

void House::createComplexDevice(QWidget* locationWidget,
                                const std::tuple<int, int, int, int, float>& parameters)
{
    int deviceTypeId = std::get<3>(parameters);
    int deviceId = std::get<2>(parameters);
    float value = std::get<4>(parameters);

    DeviceType type = static_cast<DeviceType>(deviceTypeId);
    Device* device = m_deviceFactory->createComplexDevice(type, deviceId, value);
    m_devices.insert(type, device);

    int positionX = std::get<0>(parameters);
    int positionY = std::get<1>(parameters);

    Model* model = new Model(type, device, locationWidget, positionX, positionY);
    m_model.push_back(model);

    setId(deviceId);
}

void House::setId(int value)
{
    m_id = (value > m_id) ? value : m_id;
}

void House::deleteDevice(int id)
{
    for(auto it = m_devices.begin(); it != m_devices.end(); ++it)
    {
        if (id == it.value()->getId())
        {
            m_devices.erase(it);
            break;
        }
    }

    m_model.erase(std::remove_if(m_model.begin(), m_model.end(), [id](const auto& it)
    {
        if (it->getId() == id)
        {
            delete it;
        }
        return (it->getId() == id);
    }), m_model.end());

    m_jsonManager->write(m_devices, m_model);
    sendMessageAboutDeviceDeletion(id);
}

void House::sendMessageAboutDeviceDeletion(int id)
{
    DeleteDeviceNetMessage* msg = new DeleteDeviceNetMessage();
    msg->setId(id);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);

    NetObject::getInstance().registerMessage(MessageType::DeleteDevice, m_id);
    NetObject::getInstance().sendMessage(data);

    delete msg;
}

void House::updateDiapasonValue(int id, int value, bool isSendMessage)
{
    for(auto it = m_devices.begin(); it != m_devices.end(); ++it)
    {
        if (id == it.value()->getId())
        {
            updateValue(it.key(), it.value(), value);

            m_jsonManager->write(m_devices, m_model);
            break;
        }
    }

    auto model = std::find_if(m_model.begin(), m_model.end(), [id](auto iter)
    {
        return iter->getId() == id;
    });

    if (model != m_model.end())
    {
        (*model)->setBackground(value);
    }

    m_jsonManager->write(m_devices, m_model);

    if (isSendMessage)
    {
        sendMessageAboutDeviceUpdateValue(id, value);
    }
}

void House::updateValue(DeviceType type, Device* device, int value)
{
    switch (type)
    {
        case DeviceType::ComplexLamp:
        {
            ComplexLamp* lamp = dynamic_cast<ComplexLamp*>(device);
            lamp->setDiapasonValue(value);
            break;
        }
        case DeviceType::Jalousie:
        {
            Jalousie* jalousie = dynamic_cast<Jalousie*>(device);
            jalousie->setDiapasonValue(value);
            break;
        }
        case DeviceType::Door:
        {
            Door* door = dynamic_cast<Door*>(device);
            door->setDiapasonValue(value);
            break;
        }
        case DeviceType::Battery:
        {
            Battery* battery = dynamic_cast<Battery*>(device);
            battery->setDiapasonValue(value);
            break;
        }
        case DeviceType::SimpleLamp:
        case DeviceType::Ventilator:
        {
            changeSimpleDeviceStatus(type, device);
            break;
        }
        case DeviceType::None:
        {
            Q_ASSERT(!"Invalid device type!");
            break;
        }
    }
}

void House::changeSimpleDeviceStatus(DeviceType type, Device* device)
{

    if (type == DeviceType::SimpleLamp)
    {
        SimpleLamp* lamp = dynamic_cast<SimpleLamp*>(device);
        if (lamp->isTurnOn())
        {
            lamp->turnOff();
        }
        else
        {
            lamp->turnOn();
        }
    }
    else if(type == DeviceType::Ventilator)
    {
        Ventilator* ventilator = dynamic_cast<Ventilator*>(device);
        if (ventilator->isTurnOn())
        {
            ventilator->turnOff();
        }
        else
        {
            ventilator->turnOn();
        }
    }
}

void House::sendMessageAboutDeviceUpdateValue(int id, int value)
{
    UpdateDeviceValueNetMessage* msg = new UpdateDeviceValueNetMessage();
    msg->setId(id);
    msg->setValue(value);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);

    NetObject::getInstance().registerMessage(MessageType::UpdateDeviceStatus, m_id);
    NetObject::getInstance().sendMessage(data);

    delete msg;
}

int House::getValue(DeviceType type, int id) const
{
    for(auto it = m_devices.begin(); it != m_devices.end(); ++it)
    {
        if (id != it.value()->getId())
        {
            continue;
        }

        if (type == DeviceType::SimpleLamp)
        {
            SimpleLamp* device = dynamic_cast<SimpleLamp*>(it.value());
            return (device->isTurnOn()) ? 100 : 0;
        }
        else if (type == DeviceType::ComplexLamp)
        {
            ComplexLamp* device = dynamic_cast<ComplexLamp*>(it.value());
            return device->getDiapasonValue();
        }
        else if (type == DeviceType::Door)
        {
            Door* device = dynamic_cast<Door*>(it.value());
            return device->getDiapasonValue();
        }
        else if (type == DeviceType::Battery)
        {
            Battery* device = dynamic_cast<Battery*>(it.value());
            return device->getDiapasonValue();
        }
        else if (type == DeviceType::Jalousie)
        {
            Jalousie* device = dynamic_cast<Jalousie*>(it.value());
            return device->getDiapasonValue();
        }
        else if (type == DeviceType::Ventilator)
        {
            Ventilator* device = dynamic_cast<Ventilator*>(it.value());
            return (device->isTurnOn()) ? 100 : 0;
        }
    }

    Q_ASSERT(!"Invalid device parameters!");
    return 0;
}

void House::updateDevicePosition(int id, int positionX, int positionY)
{
    m_jsonManager->write(m_devices, m_model);
    sendMessageAboutUpdatePosition(id, positionX, positionY);

}

void House::sendMessageAboutUpdatePosition(int id, int positionX, int positionY)
{
    UpdateDevicePosition* msg = new UpdateDevicePosition();
    msg->setId(id);
    msg->setPosition(positionX, positionY);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);

    NetObject::getInstance().registerMessage(MessageType::UpdateDevicePosition, id);
    NetObject::getInstance().sendMessage(data);

    delete msg;
}
