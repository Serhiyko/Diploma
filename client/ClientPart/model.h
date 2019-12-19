#ifndef MODEL_H
#define MODEL_H

#include <QJsonObject>
#include <QLabel>
#include <QMouseEvent>

#include "device.h"

class Model : public QLabel
{
    Q_OBJECT
public:
    Model(DeviceType type, Device *device, QWidget* parent = nullptr, int posX = -1,
          int posY = -1);
    ~Model() {}

    QString getObjectName() const { return this->objectName(); }

    inline int getId() const { return m_id; }
    inline LocationType getLocationType() const { return m_locationType; }

    void setBackground(int value);

    inline int getX() const { return this->pos().x(); }
    inline int getY() const { return this->pos().y(); }

    void serialize(QJsonObject& object);

protected slots:
    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

    void mouseDoubleClickEvent(QMouseEvent* event);

signals:
    void clicked();

private:
    int getObjectParameters(DeviceType type, Device* device);
    QString getPath(DeviceType type);

private:
    int m_id;
    QPoint m_startPoint;

    DeviceType m_type;
    LocationType m_locationType;

    bool m_isMovingIsActivate;
};

#endif // MODEL_H
