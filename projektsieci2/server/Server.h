#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QObject>

#include <QHash>
#include <QTcpSocket>
#include "Game_state.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr, int numPlayers = 0);

signals:
    void newMessage(const QByteArray &ba);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();
    void onNewMessage(const QByteArray &ba);

private:
    int numPlayers;
    Game_state game_state;
    QString getClientKey(const QTcpSocket *client) const;

    QTcpServer _server;
    QHash<int, QTcpSocket*> _clients;

};

#endif
