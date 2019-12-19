#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QMultiMap>
#include <QVector>

#include "constants.h"
#include "device.h"
#include "model.h"
#include "ui_mainwindow.h"


class JsonManager
{
public:
    JsonManager(){}

    void write(QMultiMap<DeviceType, Device*>& devices, QVector<Model*>& models);
    void read(const Ui::MainWindow* window);

private:
    QJsonDocument serialize(QMultiMap<DeviceType, Device*>& devices, QVector<Model*>& models);
    void deserialize(const QJsonArray& deviceContainer, const Ui::MainWindow* window);
};

#endif // JSONMANAGER_H
