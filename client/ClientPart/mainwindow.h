#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>

#include "constants.h"
#include "jsonmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Create Simple Lamp
    void on_actionSimple_Lamp_triggered();

    //Create Complex Lamp
    void on_actionComplex_Lamp_triggered();

    //Create Jalousie
    void on_actionJalousie_triggered();

    //Create Ventilator
    void on_actionVentilator_triggered();

    //Create Door
    void on_actionDoor_triggered();

    //Create Battery
    void on_actionBattery_triggered();

    void on_tabWidget_tabBarClicked(int index);

private:
    bool check_devices;

    Ui::MainWindow *ui;
    QWidget* m_widget;

    JsonManager* m_jsonManager;
};

#endif // MAINWINDOW_H
