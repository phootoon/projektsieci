#include "Server.h"
#include "Game_state.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QObject>
#include <random>
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

int getKeyByValue(QHash<int, QTcpSocket*>& hash, QTcpSocket* var) {
    for (auto it = hash.constBegin(); it != hash.constEnd(); ++it) {
        if (it.value() == var) {
            return it.key();
        }
    }
    return -1;
}

QByteArray serializeArray(const std::vector<bool>& dataArray, int size) {
    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    int arraySize = dataArray.size();
    stream << arraySize;

    std::vector<char> charArray(dataArray.begin(), dataArray.end());

    stream.writeRawData(charArray.data(), charArray.size());

    return serializedData;
}

int deserializeIntt(const QByteArray& byteArray)
{
    int result = 0;
    QDataStream stream(byteArray);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> result;

    return result;
}

QByteArray serializeInt(int data) {
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << data;

    return byteArray;
}

int findFreeSlot(const std::vector<bool>& boolArray) {
    for (int i = 0; i < boolArray.size(); ++i) {
        if (boolArray[i]) {
            return i;
        }
    }
    return -1;
}

float generateRandomFloat() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(gen);
}

TcpServer::TcpServer(QObject *parent,  int numPlayers) : QObject(parent), game_state(numPlayers), numPlayers(numPlayers)
{
    connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
    connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
    if(_server.listen(QHostAddress::Any, 45000)) {
        qInfo() << "Listening ...";
    }
}

void TcpServer::onNewConnection()
{
    int ix = findFreeSlot(game_state.getConnectedStatus());
    game_state.setConnectedStatus(ix, true);
    game_state.setAliveStatus(ix, true);
    const auto client = _server.nextPendingConnection();
    if(client == nullptr) {
        return;
    }

    qInfo() << "New client connected.";

    _clients.insert(ix, client);

    connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &TcpServer::onClientDisconnected);
}

void TcpServer::onReadyRead(){
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }

    auto message = client->readAll();
    int ix;
    int command;
    int target;
    float prob;
    using Clock = std::chrono::high_resolution_clock;
    int dsMessage = deserializeIntt(message);
    auto now = Clock::now();
    if (ix >= 0 and ix < numPlayers){
        switch(command){
        // case 0:
        //     jestem aktywny
        case 1:
            //strzelam
            target = game_state.getTarget(ix);
            prob = calculateProb(game_state.getAimTS(ix), now);
            if (prob > generateRandomFloat()){
                QTcpSocket* client = _clients.value(target, nullptr);
                client->write(0);
                auto message = serializeArray(game_state.getAliveStatus(), numPlayers);
                emit newMessage(message);
            }

        case 2:
            //celuję
            game_state.setAimTS(ix, now);
        case 3:
            //zmieniam cel w prawo
            target = game_state.getTarget(ix);
            if  (target >= 0 and target < numPlayers - 1){
                game_state.setTarget(ix, target + 1);
            }
        case 4:
            //zmieniam cel w lewo
            target = game_state.getTarget(ix);
            if  (target > 0 and target < numPlayers){
                game_state.setTarget(ix, target - 1);
            }
        case 5:
            //zgłaszam gotowość
            game_state.setReady(ix, true);
        case 6:
            game_state.setVote(ix, true);
        }
    }
}

void TcpServer::onClientDisconnected()
{
    const auto client = qobject_cast<QTcpSocket*>(sender());

    if(client == nullptr) {
        return;
    }
    auto clientToRemove = getKeyByValue(_clients, client);
    game_state.deletePlayer(clientToRemove, game_state);
    _clients.remove(clientToRemove);
}

void TcpServer::onNewMessage(const QByteArray &ba)
{
    for(const auto &client : std::as_const(_clients)) {
        client->write(ba);
        client->flush();
    }
}
