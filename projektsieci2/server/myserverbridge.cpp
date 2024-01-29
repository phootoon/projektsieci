#include "MyServerBridge.h"

MyServerBridge::MyServerBridge(QObject* parent) : QObject(parent) {
}

void MyServerBridge::onNewConnection()
{
    emit newConnection();
}

void MyServerBridge::onReadyRead(int i, char message)
{
    emit readyRead(i, message);
}


void MyServerBridge::onClientDisconnected(int i)
{
    emit clientDisconnected(i);
}
