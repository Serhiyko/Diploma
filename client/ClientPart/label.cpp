#include "label.h"
#include <QDebug>

Label::Label(const QString &path, QWidget *parent) : QLabel(parent)
{
    QLabel* lable = new QLabel;
    lable->setText("Test");
    //lable->setObjectName("Object" + QString::number(_devices.last()->getId()));
    lable->setPixmap(QPixmap("C:/Users/serjo/OneDrive/QT/Dyploma/images.jpg"));
    lable->setGeometry(100, 100, 200, 150);
    lable->show();

    //connect(lable, SIGNAL(onClick), this, SLOT(Click()));
}

Label::~Label()
{

}

void Label::mousePressEvent(QMouseEvent *ev)
{

}

void Label::Click()
{
    qDebug() << "click...";
}

