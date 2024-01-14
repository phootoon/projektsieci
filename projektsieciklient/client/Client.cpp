#include "Client.h"
#include <QByteArray>
#include <QDataStream>
#include "Game_state_client.h"

int findFirstDifferenceIndex(const QVector<bool>& qVector, const std::vector<bool>& stdVector) {

    for (int i = 0; i < stdVector.size(); ++i) {
        if (qVector[i] != stdVector[i]) {
            return i;
        }
    }
    return -1;
}


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

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

    // QTcpSocket _socket(nullptr);
    QTcpSocket *_socket = new QTcpSocket(this);
    connect(_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);

}

void TcpClient::connectToServer(const QString &ip, const QString &port)
{
    // _socket.connectToHost(ip, port.toUInt());

    _socket->connectToHost(QHostAddress::LocalHost, 12345);
    if(_socket->waitForConnected()){
        qInfo() << "client created.";
    }
}

void TcpClient::sendMessage(const QByteArray &message)
{
    qInfo() << "message sent.";
    _socket->write(message);
    _socket->flush();

}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host.";
}

void TcpClient::onReadyRead()
{
    qInfo() << "message read.";
    Game_state_client* game_state = new Game_state_client(1);
    const auto message = _socket->readAll();
    if (message.length() == 4){
        int dsMessage = deserializeInt(message);
        if(dsMessage == 0){
            emit showDeathScreen();
        }
        else{
            Game_state_client* game_state = new Game_state_client(dsMessage);
            //moze powodawac błąd
        }
    }
    else{
        QVector<bool> alive_status_vec = deserializeQByteArray(message);
        emit statusChanged(message);
        for (int i = 0; i < alive_status_vec.size(); ++i)
        {
            game_state->setAliveStatus(i, alive_status_vec.at(i));
        }
    }
}
void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
