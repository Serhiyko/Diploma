#-------------------------------------------------
#
# Project created by QtCreator 2018-02-05T20:37:12
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClientPart
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    device.cpp \
    jsonmanager.cpp \
        main.cpp \
        mainwindow.cpp \
    complexdevice.cpp \
    netmessage.cpp \
    netobject.cpp \
    simpledevice.cpp \
    model.cpp \
    propertiesframe.cpp \
    devicefactory.cpp \
    house.cpp

HEADERS += \
    constants.h \
    jsonmanager.h \
        mainwindow.h \
    device.h \
    complexdevice.h \
    netmessage.h \
    netobject.h \
    simpledevice.h \
    model.h \
    propertiesframe.h \
    devicefactory.h \
    house.h

FORMS += \
        mainwindow.ui \
    propertiesframe.ui

unix|win32: LIBS += -lWS2_32
