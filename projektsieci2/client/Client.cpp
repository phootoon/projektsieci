#include "Client.h"
#include <QByteArray>
#include <QDataStream>



QVector<bool> deserializeQByteArray(const QByteArray& byteArray)
{
    QVector<bool> result;

    QDataStream stream(byteArray);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd())
    {
        bool element;
        stream >> element;
        result.append(element);
    }

    return result;
}

int deserializeInt(const QByteArray& byteArray)
{
    int result = 0;
    QDataStream stream(byteArray);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> result;

    return result;
}

TcpClient::TcpClient(QObject *parent, int numPlayers) : QObject(parent), game_state(numPlayers), numPlayers(numPlayers)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, const QString &port)
{
    _socket.connectToHost(ip, port.toUInt());
}

void TcpClient::sendMessage(const QByteArray &message)
{
    _socket.write(message);
    _socket.flush();
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host.";
}

void TcpClient::onReadyRead()
{
    const auto message = _socket.readAll();
    if (message.length() == 1){
        //wyświetl death screen
    }
    else{
        bool alive_status[numPlayers];
        QVector<bool> alive_status_vec = deserializeQByteArray(message);
        for (int i = 0; i < alive_status_vec.size(); ++i)
        {
            game_state.setAliveStatus(i, alive_status_vec.at(i));
        }
    }

}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
