#include "Server.h"
#include "Game_state.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QIODevice>

float calculateProb(std::chrono::time_point<std::chrono::high_resolution_clock> then,
                    std::chrono::time_point<std::chrono::high_resolution_clock> now) {

    std::chrono::duration<float> elapsed_seconds = now - then;
    float fraction = elapsed_seconds.count() / 5.0f;
    fraction = std::min(std::max(fraction, 0.0f), 1.0f);
    float probability = fraction * fraction;

    return probability;
}

int getKeyByValue(QHash<int,int>& hash, int client) {
    for (auto it = hash.constBegin(); it != hash.constEnd(); ++it) {
        if (it.value() == client) {
            return it.key();
        }
    }
    return -1;
}

int findFreeSlot(const std::vector<bool>& boolArray) {
    for (int i = 0; i < boolArray.size(); ++i) {
        if (! boolArray[i]) {
            return i;
        }
    }
    return -1;
}

double getRandomNumber() {
    srand((unsigned int)time(NULL));
    int randomInt = rand();
    double randomDouble = (double)randomInt / RAND_MAX;

    return randomDouble;
}

TcpServer::TcpServer(QObject *parent,  int numPlayers) : QObject(parent), game_state(numPlayers), numPlayers(numPlayers), _server(45000,numPlayers)
{
    connect(&_server.getServerBridge(), &MyServerBridge::newConnection, this, &TcpServer::onNewConnection);
    connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
    connect(&_server.getServerBridge(),&MyServerBridge::readyRead, this, &TcpServer::onReadyRead);
    connect(this, &TcpServer::clientDisconnected, this, &TcpServer::onClientDisconnected);
    _server.run();
}

void TcpServer::onNewConnection()
{
    int ix = findFreeSlot(game_state.getConnectedStatus());
    game_state.setConnectedStatus(ix, true);
    game_state.setAliveStatus(ix, true);
    game_state.setTarget(ix, 0);
    const int client = _server.nextPendingConnection();

    //wysłać alivestatus
    std::vector<bool> vec = game_state.getAliveStatus();
    std::vector<char> charVector(vec.begin(), vec.end());
    int x = send(client, charVector.data(), numPlayers, 0);
    if(client == -1) {
        return;
    }

    qInfo() << "New client connected.";

    _clients.insert(ix, client);
}

void TcpServer::onReadyRead(int client){
    qInfo() << "wiadomosc";

    if(client == -1) {
        return;
    }
    //czytaj
    char message;
    int bytesRead = recv(client, &message, 1, 0);
    if (bytesRead == 0){
        //emit clientDisconnected(client);
        return;
    }
    int ix = getKeyByValue(_clients, client);
    int target;
    double prob;
    using Clock = std::chrono::high_resolution_clock;
    auto now = Clock::now();
    if (ix >= 0 and ix < numPlayers){
        switch(message){
        case '1':
            qInfo() << "strzelam";
            //strzelam
            target = game_state.getTarget(ix);
            prob = calculateProb(game_state.getAimTS(ix), now);
            if (prob > getRandomNumber()){
                qInfo() << "trafiony";
                int deadClient = _clients.value(target);
                char msg = '0';
                send(deadClient, &msg, 1, 0);
                game_state.setAliveStatus(ix, false);
                auto message = game_state.getAliveStatus();
                emit newMessage(message);
            }
            break;
        case '2':
            //celuję
            game_state.setAimTS(ix, now);
            break;
        case '3':
            //zmieniam cel w prawo
            target = game_state.getTarget(ix);
            if  (target >= 0 and target < numPlayers - 1){
                game_state.setTarget(ix, target + 1);
            }
            break;
        case '4':
            //zmieniam cel w lewo
            target = game_state.getTarget(ix);
            if  (target > 0 and target < numPlayers){
                game_state.setTarget(ix, target - 1);
            }
            break;
        }
    }
}

void TcpServer::onClientDisconnected(int client)
{

    if(client == -1) {
        return;
    }
    auto clientToRemove = getKeyByValue(_clients, client);
    game_state.deletePlayer(clientToRemove, game_state);
    _clients.remove(clientToRemove);
}

void TcpServer::onNewMessage(const std::vector<bool> &ba)
{
    std::vector<char> charVector(ba.begin(), ba.end());
    for(const auto &client : std::as_const(_clients)) {
        send(client, charVector.data(), numPlayers, 0);
    }
}
