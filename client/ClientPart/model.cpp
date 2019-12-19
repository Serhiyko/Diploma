#include "model.h"
#include <QDebug>
#include <QPointer>

#include "complexdevice.h"
#include "house.h"
#include "propertiesframe.h"
#include "simpledevice.h"

Model::Model(DeviceType type, Device* device, QWidget *parent, int posX, int posY) : QLabel(parent)
{
    m_isMovingIsActivate = false;

    m_type = type;

    const auto& label = parent->objectName();
    if (label == "label_1")
    {
        m_locationType = LocationType::FirstFloor;
    }
    else if (label == "label_2")
    {
        m_locationType = LocationType::SecondFloor;
    }

    QString path = getPath(type);

    this->setPixmap(QPixmap(path));
    int x = (posX == -1) ? 500 : posX;
    int y = (posY == -1) ? 200 : posY;

    this->setGeometry(x, y, 50, 50);

    m_id = device->getId();

    int value = getObjectParameters(type, device);
    setBackground(value);

    this->setAlignment(Qt::AlignCenter);
    this->show();
}

void Model::serialize(QJsonObject& object)
{
    object.insert("locationId", static_cast<int>(m_locationType));
    object.insert("positionX", this->pos().x());
    object.insert("positionY", this->pos().y());
}

int Model::getObjectParameters(DeviceType type, Device* device)
{
    switch (type)
    {
        case DeviceType::SimpleLamp:
        {
            SimpleLamp* object = dynamic_cast<SimpleLamp*>(device);
            return (object->isTurnOn()) ? 100.0f : 0.0f;
        }
        case DeviceType::ComplexLamp:
        {
            ComplexLamp* object = dynamic_cast<ComplexLamp*>(device);
            return object->getDiapasonValue();
        }
        case DeviceType::Ventilator:
        {
            Ventilator* object = dynamic_cast<Ventilator*>(device);
            return (object->isTurnOn()) ? 100.0f : 0.0f;
        }
        case DeviceType::Jalousie:
        {
            Jalousie* object = dynamic_cast<Jalousie*>(device);
            return object->getDiapasonValue();
        }
        case DeviceType::Door:
        {
            Door* object = dynamic_cast<Door*>(device);
            return object->getDiapasonValue();
        }
        case DeviceType::Battery:
        {
            Battery* object = dynamic_cast<Battery*>(device);
            return object->getDiapasonValue();
        }
        case DeviceType::None:
        {
            Q_ASSERT(!"Invalid DeviceType");
            break;
        }
    }
}

QString Model::getPath(DeviceType type)
{
    switch (type)
    {
        case DeviceType::SimpleLamp:
        {
            return "../Pictures/light1.png";
        }
        case DeviceType::ComplexLamp:
        {
            return "../Pictures/light2.png";
        }
        case DeviceType::Ventilator:
        {
            return "../Pictures/windmill.png";
        }
        case DeviceType::Jalousie:
        {
            return "../Pictures/jalousie.png";
        }
        case DeviceType::Door:
        {
            return "../Pictures/doorway.png";
        }
        case DeviceType::Battery:
        {
            return "../Pictures/floor.png";
        }
        default: return "";
    }
}

void Model::mousePressEvent(QMouseEvent* event)
{
    if((event->button() == Qt::RightButton) && !m_isMovingIsActivate)
    {
        auto frame = QPointer<PropertiesFrame>(new PropertiesFrame(m_id, m_type));
        frame->show();
    }
}

void Model::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_isMovingIsActivate)
    {
        return;
    }

    QPoint currentPos = event->pos();

    int deltaX = currentPos.x() - m_startPoint.x();
    int deltaY = currentPos.y() - m_startPoint.y();

    int newX= this->pos().x() + deltaX;
    int newY = this->pos().y() + deltaY;

    this->setGeometry(newX, newY, 50, 50);
}

void Model::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isMovingIsActivate = (m_isMovingIsActivate) ? false : true;
        qDebug() << "double clicked: " << m_isMovingIsActivate;

        if (!m_isMovingIsActivate)
        {
            qDebug() << "current position: " << this->pos();
            House::getInstance().updateDevicePosition(m_id, this->pos().x(), this->pos().y());
        }
    }
}

void Model::setBackground(int value)
{
    if(value == 0)
    {
        this->setStyleSheet("QLabel { background-color : white; }");
    }
    else
    {
        this->setStyleSheet("QLabel { background-color : yellow; }");
    }
}
