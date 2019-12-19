#include "jsonmanager.h"

#include <QJsonObject>
#include "house.h"

void JsonManager::write(QMultiMap<DeviceType, Device*>& devices, QVector<Model*>& models)
{
    QJsonDocument document = serialize(devices, models);

    QFile file("../ClientPart/data.json");

    file.open(QIODevice::WriteOnly);
    if(file.isOpen())
    {
        file.write(document.toJson());
    }

    file.close();
}

QJsonDocument JsonManager::serialize(QMultiMap<DeviceType, Device*>& devices, QVector<Model*>& models)
{
    QJsonArray devicesJsonContainer;

    for (const auto& device: devices)
    {
        QJsonObject object;
        device->serialize(object);

        auto id = device->getId();
        for (const auto& model: models)
        {
            if (id == model->getId())
            {
                model->serialize(object);
                break;
            }
        }

        devicesJsonContainer.push_back(object);
    }

    QJsonDocument document;
    document.setArray(devicesJsonContainer);

    return document;
}

void JsonManager::read(const Ui::MainWindow* window)
{
    QJsonDocument document;
    QFile file("../ClientPart/data.json");

    file.open(QIODevice::ReadOnly);
    if (file.isOpen())
    {
       document = QJsonDocument().fromJson(file.readAll());
    }

    file.close();

    if (document.isArray())
    {
        deserialize(document.array(), window);
    }
}

void JsonManager::deserialize(const QJsonArray& deviceContainer, const Ui::MainWindow* window)
{
    for (int i = 0; i < deviceContainer.size(); ++i)
    {
        QJsonObject device = deviceContainer[i].toObject();

        int deviceId = device.value("id").toInt();

        int locationId = device.value("locationId").toInt();
        QWidget* locationWidget = (locationId == 0) ? window->label_1 : window->label_2;

        int positionX = device.value("positionX").toInt();
        int positionY = device.value("positionY").toInt();

        int deviceTypeId = device.value("device_type").toInt();
        DeviceType deviceType = static_cast<DeviceType>(deviceTypeId);
        switch (deviceType)
        {
            case DeviceType::SimpleLamp:
            {
                bool isTurnOn = device.value("turnOn").toBool();
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, isTurnOn);
                House::getInstance().createSimpleDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::ComplexLamp:
            {
                float value = static_cast<float>(device.value("value").toDouble());
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, value);
                House::getInstance().createComplexDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::Door:
            {
                float value = static_cast<float>(device.value("value").toDouble());
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, value);
                House::getInstance().createComplexDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::Battery:
            {
                float value = static_cast<float>(device.value("value").toDouble());
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, value);
                House::getInstance().createComplexDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::Jalousie:
            {
                float value = static_cast<float>(device.value("value").toDouble());
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, value);
                House::getInstance().createComplexDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::Ventilator:
            {
                bool isTurnOn = device.value("turnOn").toBool();
                auto parameters = std::make_tuple(positionX, positionY, deviceId, deviceTypeId, isTurnOn);
                House::getInstance().createSimpleDevice(locationWidget, parameters);
                break;
            }
            case DeviceType::None:
            {
                break;
            }
        }
    }
}
