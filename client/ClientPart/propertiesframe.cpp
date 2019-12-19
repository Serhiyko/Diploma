#include "propertiesframe.h"
#include "ui_propertiesframe.h"

#include <QByteArray>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QPointer>

#include "house.h"
#include "netobject.h"
#include "netmessage.h"

PropertiesFrame::PropertiesFrame(int id, DeviceType type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PropertiesFrame)
{
    ui->setupUi(this);

    m_id = id;
    m_type = type;

    m_deviceValue = House::getInstance().getValue(type, id);

    if (isDeviceSimple())
    {
        ui->verticalSlider->hide();
        ui->applyValueButton->hide();
        ui->horizontalValueBar->setPageStep(100);
    }
    else
    {
        ui->verticalSlider->setValue(m_deviceValue);
        connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(onChangeDiapason(int)));
    }

    ui->imagelabel->setPixmap(getImagePath());
}

PropertiesFrame::~PropertiesFrame()
{
    delete ui;
}

QString PropertiesFrame::getImagePath()
{
    switch (m_type)
    {
        case DeviceType::SimpleLamp:
        {
            return "../Pictures/SLamp.png";
        }
        case DeviceType::ComplexLamp:
        {
            return "../Pictures/CLamp.png";
        }
        case DeviceType::Ventilator:
        {
            return "../Pictures/fan.png";
        }
        case DeviceType::Jalousie:
        {
            return "../Pictures/CJalousie.png";
        }
        case DeviceType::Door:
        {
            return "../Pictures/door.png";
        }
        case DeviceType::Battery:
        {
            return "../Pictures/underfloor-heating.png";
        }
        case DeviceType::None:
        {
            Q_ASSERT(!"Invalid device type!");
        }
    }

    return "";
}

void PropertiesFrame::on_closeButton_clicked()
{
    House::getInstance().deleteDevice(m_id);
    m_id = 0;
    this->close();
}

void PropertiesFrame::on_turnOnOffButton_clicked()
{
    qDebug() << "device with id " << QString::number(m_id);
    m_deviceValue = (m_deviceValue > 0) ? 0 : 99;
    if (!isDeviceSimple())
    {
        ui->verticalSlider->setValue(m_deviceValue);
    }

    House::getInstance().updateDiapasonValue(m_id, m_deviceValue);
}

void PropertiesFrame::on_deviceTabWidget_currentChanged(int index)
{
    qDebug() << "swap = " << index;
}

void PropertiesFrame::onChangeDiapason(int value)
{
    m_deviceValue = value;
}

void PropertiesFrame::on_dateTimeButton_clicked()
{
    QDateTime dateTime;
    dateTime.setDate(ui->calendarWidget->selectedDate());
    dateTime.setTime(ui->timeEdit->time());

    if (dateTime <= QDateTime::currentDateTime())
    {
        QMessageBox box;
        box.setText("Invalid date and time!");
        box.exec();
        return;
    }

    qDebug() << dateTime.time().toString("HH:mm:ss") << "||" << dateTime.date().toString("dd.MM.yyyy");

    int value = ui->horizontalValueBar->value();

    SetDateTimeInfoMessage* msg = new SetDateTimeInfoMessage();
    msg->setId(m_id);
    msg->setValue(value);
    msg->setDataTime(dateTime);

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);

    NetObject::getInstance().registerMessage(MessageType::SetDateTimeEvent, m_id);
    NetObject::getInstance().sendMessage(data);

    delete msg;
}

bool PropertiesFrame::isDeviceSimple()
{
    return (m_type == DeviceType::SimpleLamp) || (m_type == DeviceType::Ventilator);
}

void PropertiesFrame::on_applyValueButton_clicked()
{
    House::getInstance().updateDiapasonValue(m_id, m_deviceValue);
}
