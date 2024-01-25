#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <QObject>
#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>
#include "Game_state.h"
#include "_server.h"
#include "myserverbridge.h"
#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#pragma comment(lib, "ws2_32.lib")
#endif

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr, int numPlayers = 0);
    int numberOfPlayers;

signals:
    void newMessage(const std::vector<bool> &ba);
    void clientDisconnected(int i);

private slots:
    void onNewConnection();
    void onReadyRead(int client);
    void onClientDisconnected(int client);
    void onNewMessage(const std::vector<bool> &ba);


private:
    int numPlayers;
    Game_state game_state;
    QString getClientKey(const QTcpSocket *client) const;

    Server _server;
    QHash<int, int> _clients;

};

#endif
