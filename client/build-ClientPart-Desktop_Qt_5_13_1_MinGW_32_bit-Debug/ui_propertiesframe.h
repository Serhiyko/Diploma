/********************************************************************************
** Form generated from reading UI file 'propertiesframe.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESFRAME_H
#define UI_PROPERTIESFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PropertiesFrame
{
public:
    QPushButton *propertiesButton;
    QPushButton *closeButton;

    void setupUi(QFrame *PropertiesFrame)
    {
        if (PropertiesFrame->objectName().isEmpty())
            PropertiesFrame->setObjectName(QString::fromUtf8("PropertiesFrame"));
        PropertiesFrame->resize(131, 40);
        PropertiesFrame->setFrameShape(QFrame::StyledPanel);
        PropertiesFrame->setFrameShadow(QFrame::Raised);
        propertiesButton = new QPushButton(PropertiesFrame);
        propertiesButton->setObjectName(QString::fromUtf8("propertiesButton"));
        propertiesButton->setGeometry(QRect(0, 0, 131, 21));
        closeButton = new QPushButton(PropertiesFrame);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(0, 20, 131, 21));

        retranslateUi(PropertiesFrame);

        QMetaObject::connectSlotsByName(PropertiesFrame);
    } // setupUi

    void retranslateUi(QFrame *PropertiesFrame)
    {
        PropertiesFrame->setWindowTitle(QCoreApplication::translate("PropertiesFrame", "Frame", nullptr));
        propertiesButton->setText(QCoreApplication::translate("PropertiesFrame", "Properties", nullptr));
        closeButton->setText(QCoreApplication::translate("PropertiesFrame", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertiesFrame: public Ui_PropertiesFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESFRAME_H
