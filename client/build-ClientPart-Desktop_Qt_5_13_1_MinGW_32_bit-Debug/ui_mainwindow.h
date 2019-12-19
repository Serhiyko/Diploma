/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionJalousie;
    QAction *actionSimple_Lamp;
    QAction *actionComplex_Lamp;
    QAction *actionVentilator;
    QAction *actionDoor;
    QAction *actionBattery;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *F_Floor;
    QLabel *label_1;
    QWidget *S_Floor;
    QLabel *label_2;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuCreate;
    QMenu *menuLamp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(770, 666);
        actionJalousie = new QAction(MainWindow);
        actionJalousie->setObjectName(QString::fromUtf8("actionJalousie"));
        actionSimple_Lamp = new QAction(MainWindow);
        actionSimple_Lamp->setObjectName(QString::fromUtf8("actionSimple_Lamp"));
        actionComplex_Lamp = new QAction(MainWindow);
        actionComplex_Lamp->setObjectName(QString::fromUtf8("actionComplex_Lamp"));
        actionVentilator = new QAction(MainWindow);
        actionVentilator->setObjectName(QString::fromUtf8("actionVentilator"));
        actionDoor = new QAction(MainWindow);
        actionDoor->setObjectName(QString::fromUtf8("actionDoor"));
        actionBattery = new QAction(MainWindow);
        actionBattery->setObjectName(QString::fromUtf8("actionBattery"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 30, 710, 481));
        F_Floor = new QWidget();
        F_Floor->setObjectName(QString::fromUtf8("F_Floor"));
        label_1 = new QLabel(F_Floor);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(20, 20, 700, 400));
        tabWidget->addTab(F_Floor, QString());
        S_Floor = new QWidget();
        S_Floor->setObjectName(QString::fromUtf8("S_Floor"));
        label_2 = new QLabel(S_Floor);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 671, 471));
        tabWidget->addTab(S_Floor, QString());
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 530, 701, 70));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 770, 20));
        menuCreate = new QMenu(menuBar);
        menuCreate->setObjectName(QString::fromUtf8("menuCreate"));
        menuLamp = new QMenu(menuCreate);
        menuLamp->setObjectName(QString::fromUtf8("menuLamp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCreate->menuAction());
        menuCreate->addAction(menuLamp->menuAction());
        menuCreate->addAction(actionJalousie);
        menuCreate->addAction(actionVentilator);
        menuCreate->addAction(actionDoor);
        menuCreate->addAction(actionBattery);
        menuLamp->addAction(actionSimple_Lamp);
        menuLamp->addAction(actionComplex_Lamp);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionJalousie->setText(QCoreApplication::translate("MainWindow", "Jalousie", nullptr));
        actionSimple_Lamp->setText(QCoreApplication::translate("MainWindow", "Simple Lamp", nullptr));
        actionComplex_Lamp->setText(QCoreApplication::translate("MainWindow", "Complex Lamp", nullptr));
        actionVentilator->setText(QCoreApplication::translate("MainWindow", "Ventilator", nullptr));
        actionDoor->setText(QCoreApplication::translate("MainWindow", "Door", nullptr));
        actionBattery->setText(QCoreApplication::translate("MainWindow", "Battery", nullptr));
        label_1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(F_Floor), QCoreApplication::translate("MainWindow", "1 Floor", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(S_Floor), QCoreApplication::translate("MainWindow", "2 Floor", nullptr));
        menuCreate->setTitle(QCoreApplication::translate("MainWindow", "Create", nullptr));
        menuLamp->setTitle(QCoreApplication::translate("MainWindow", "Lamp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
