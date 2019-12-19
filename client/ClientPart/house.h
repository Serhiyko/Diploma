#ifndef HOUSE_H
#define HOUSE_H

#include <tuple>

#include <QVector>
#include <QMultiMap>
#include <QWidget>
#include <QXmlStreamWriter>
#include <QFile>

#include "devicefactory.h"
#include "jsonmanager.h"
#include "model.h"

class House
{
public:
    static House& getInstance();

    void createDevices(DeviceType type, QWidget* widget);
    void createSimpleDevice(QWidget* locationWidget,
                            const std::tuple<int, int, int, int, bool>& parameters);
    void createComplexDevice(QWidget* locationWidget,
                             const std::tuple<int, int, int, int, float>& parameters);

    void deleteDevice(int id);
    void updateDiapasonValue(int id, int value, bool isSendMessage = true);
    int getValue(DeviceType type, int id) const;

    void updateDevicePosition(int id, int positionX, int positionY);

private:
    House();
    ~House();

    void setId(int value);
    void updateId(int value = 0);

    void updateValue(DeviceType type, Device* device, int value);
    void changeSimpleDeviceStatus(DeviceType type, Device* device);

    void sendMessageAboutDeviceCreation(DeviceType type, const Model& model);
    void sendMessageAboutDeviceUpdateValue(int id, int value);
    void sendMessageAboutDeviceDeletion(int id);
    void sendMessageAboutUpdatePosition(int id, int positionX, int positionY);

private:
    QMultiMap<DeviceType, Device*> m_devices;
    QVector<Model*> m_model;

    int m_id;
    DeviceFactory* m_deviceFactory;
    JsonManager* m_jsonManager;
};

#endif // HOUSE_H
