#include "Client.h"
#include <QByteArray>
#include <QDataStream>
#include <QVector>

QVector<char> readBinaryDataFromSocket(QTcpSocket& socket) {
    QVector<char> binaryData;

    // Read binary data from the socket until there is no more available data
    while (socket.bytesAvailable() > 0) {
        char byte;
        qint64 bytesRead = socket.read(&byte, sizeof(byte));

        // Check if a byte was successfully read
        if (bytesRead == sizeof(byte)) {
            qInfo() << "przeczytało 1 bajt";
            binaryData.append(byte);
        }
    }
    return binaryData;
}

int findFirstDifferenceIndex(const QVector<bool>& qVector, const std::vector<bool>& stdVector) {

    for (int i = 0; i < stdVector.size(); ++i) {
        if (qVector[i] != stdVector[i]) {
            return i;
        }
    }
    return -1;
}

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer(const QString &ip, const quint16 &port)
{
    qInfo() << "connecting to host";
    _socket.connectToHost(ip, port);
}

void TcpClient::sendMessage(char message)
{
    QByteArray x;
    x.append(message);
    qInfo() << "sending message";
    _socket.write(x);
    _socket.flush();
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host.";
}

void TcpClient::onReadyRead()
{
    qInfo() << "wiadomość";
    const auto message = readBinaryDataFromSocket(_socket);
    if (message.length() == 1){
        emit showDeathScreen();
    }
    else{
        qInfo() << "client status changed";
        emit statusChanged(message);
    }
}
void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
