#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Game_state_client.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr, int numPlayers = 0);

signals:
    void newMessage(const QByteArray &ba);

public slots:
    void connectToServer(const QString &ip, const QString &port);
    void sendMessage(const QByteArray &message);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    int numPlayers;
    Game_state_client game_state;
    QTcpSocket _socket;
};

#endif
