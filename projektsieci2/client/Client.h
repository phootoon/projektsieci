#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);
    void statusChanged(const QByteArray &i);
    void showDeathScreen();

public slots:
    void connectToServer(const QString &ip, const QString &port);
    void sendMessage(const QByteArray &message);
    //void handleMovement(const QByteArray &moveData);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    int numPlayers;
    QTcpSocket _socket;
};

#endif
