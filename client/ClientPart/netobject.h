#ifndef NETOBJECT_H
#define NETOBJECT_H

#include "constants.h"

#include <QDataStream>
#include <QMultiMap>
#include <QObject>
#include <QPointer>
#include <QtNetwork/QTcpSocket>

class NetObject : public QObject
{
    Q_OBJECT
public:
    static NetObject& getInstance();

     void initConnection();
     void sendMessage(const QByteArray& message);

     void registerMessage(MessageType type, int deviceId);

     int getUserId() const;

private:
    explicit NetObject(QObject* parent = nullptr) : QObject(parent) {}
    ~NetObject() {}

    void unregisterMessage(MessageType type, int deviceId);

    void deserializeGetDateTimeEventMessage(QDataStream& stream, int deviceId);

private slots:
    void receiveMessage();

private:
    QPointer<QTcpSocket> m_socket;
    QMultiMap<MessageType, int> m_messageManager;
    int m_userId;
};

#endif // NETOBJECT_H
