#include "netobject.h"

#include <QByteArray>
#include <QHostAddress>
#include <QList>
#include <QMessageBox>

#include "house.h"

namespace
{
    QList<MessageType> availableTypes = {
        MessageType::CreateDevice,
        MessageType::UpdateDeviceStatus,
        MessageType::DeleteDevice,
        MessageType::SetDateTimeEvent,
        MessageType::GetDateTimeEvent,
        MessageType::GetDevices,
        MessageType::UpdateDevicePosition,
        MessageType::SendUserID
    };
}

NetObject& NetObject::getInstance()
{
    static NetObject* instance = new NetObject();
    return *instance;
}

void NetObject::initConnection()
{
    m_userId = 1;

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::LocalHost, 1234);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(m_socket, &QAbstractSocket::disconnected, [socket = m_socket]()
    {
        qDebug() << "DISCONNECTED";
        socket->deleteLater();
    });

    if (!m_socket->waitForConnected(3000))
    {
        QMessageBox box;
        box.setText("Not Connected!");
        box.exec();
    }
}

void NetObject::receiveMessage()
{
    QByteArray message = m_socket->readAll();
    QDataStream stream(&message, QIODevice::ReadOnly);

    if (message.size() > 0)
    {
        int messageCode = 0;
        stream >> messageCode;

        MessageType type = static_cast<MessageType>(messageCode);
        if (availableTypes.contains(type))
        {
            int deviceId = 0;
            stream >> deviceId;

            if (type == MessageType::GetDateTimeEvent)
            {
                deserializeGetDateTimeEventMessage(stream, deviceId);
            }
            else
            {
                int errorCode = 0;
                stream >> errorCode;
                if (errorCode == 1)
                {
                    unregisterMessage(type, deviceId);
                }
                else
                {
                    //TODO: update error code
                }
            }
        }
    }
}

void NetObject::sendMessage(const QByteArray& message)
{
    m_socket->write(message);
}

void NetObject::registerMessage(MessageType type, int deviceId)
{
    const auto& iter = m_messageManager.constFind(type, deviceId);
    if (iter == m_messageManager.constEnd())
    {
        m_messageManager.insert(type, deviceId);
    }
}

void NetObject::unregisterMessage(MessageType type, int deviceId)
{
    auto iter = m_messageManager.find(type, deviceId);
    m_messageManager.erase(iter);
}

int NetObject::getUserId() const
{
    return m_userId;
}

void NetObject::deserializeGetDateTimeEventMessage(QDataStream& stream, int deviceId)
{
    int userId = 0;
    stream >> userId;

    if (userId == m_userId)
    {
        int value = 0;
        stream >> value;

        House::getInstance().updateDiapasonValue(deviceId, value, false);
    }
}
