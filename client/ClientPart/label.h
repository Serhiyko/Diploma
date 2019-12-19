#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
//#include <QString>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(const QString& path, QWidget* parent = 0);
    ~Label();

public slots:
    void Click();

    void mousePressEvent(QMouseEvent* ev);

signals:
    void onClick(QWidget* widget);
};

#endif // LABEL_H
