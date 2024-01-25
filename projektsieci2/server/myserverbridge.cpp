#include "MyServerBridge.h"

MyServerBridge::MyServerBridge(QObject* parent) : QObject(parent) {
}

void MyServerBridge::onNewConnection()
{
    emit newConnection();
}

void MyServerBridge::onReadyRead(int i)
{
    emit readyRead(i);
}
