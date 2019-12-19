#ifndef PROPERTIESFRAME_H
#define PROPERTIESFRAME_H

#include <QFrame>
#include "constants.h"

namespace Ui {
class PropertiesFrame;
}

class PropertiesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PropertiesFrame(int id, DeviceType type, QWidget *parent = 0);
    ~PropertiesFrame();

private:
    QString getImagePath();
    bool isDeviceSimple();

private slots:
    void on_closeButton_clicked();

    void on_turnOnOffButton_clicked();

    void on_deviceTabWidget_currentChanged(int index);

    void onChangeDiapason(int value);

    void on_dateTimeButton_clicked();

    void on_applyValueButton_clicked();

private:
    Ui::PropertiesFrame* ui;
    int m_id;
    DeviceType m_type;
    int m_deviceValue;
};

#endif // PROPERTIESFRAME_H
