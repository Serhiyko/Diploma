#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "netobject.h"
#include "house.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    NetObject::getInstance().initConnection();
    ui->tabWidget->setCurrentIndex(0);

    ui->label_1->setPixmap(QPixmap("../Pictures/1Floor.png"));
    ui->label_1->setText("");
    ui->label_1->show();

    ui->label_2->setPixmap(QPixmap("../Pictures/2Floor.png"));
    ui->label_2->setText("");
    ui->label_2->show();

    m_widget = ui->label_1;

    m_jsonManager = new JsonManager();
    m_jsonManager->read(ui);
}

MainWindow::~MainWindow()
{
    delete m_widget;
    delete m_jsonManager;
    delete ui;
}

void MainWindow::on_actionSimple_Lamp_triggered()
{
    House::getInstance().createDevices(DeviceType::SimpleLamp, m_widget);
}

void MainWindow::on_actionComplex_Lamp_triggered()
{
    House::getInstance().createDevices(DeviceType::ComplexLamp, m_widget);
}

void MainWindow::on_actionJalousie_triggered()
{
    House::getInstance().createDevices(DeviceType::Jalousie, m_widget);
}

void MainWindow::on_actionVentilator_triggered()
{
    House::getInstance().createDevices(DeviceType::Ventilator, m_widget);
}

void MainWindow::on_actionDoor_triggered()
{
    House::getInstance().createDevices(DeviceType::Door, m_widget);
}

void MainWindow::on_actionBattery_triggered()
{
    House::getInstance().createDevices(DeviceType::Battery, m_widget);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0)
    {
        m_widget = ui->label_1;
    }
    else if(index == 1)
    {
        m_widget = ui->label_2;
    }
}
