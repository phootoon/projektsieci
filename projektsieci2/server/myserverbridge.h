#ifndef MYSERVERBRIDGE_H
#define MYSERVERBRIDGE_H

#include <QObject>

class MyServerBridge : public QObject
{
    Q_OBJECT
public:
    explicit MyServerBridge(QObject* parent = nullptr);
    void onNewConnection();
    void onReadyRead(int i, char message);
    void onClientDisconnected(int i);

signals:
    void newConnection();
    void readyRead(int i, char message);
    void clientDisconnected(int i);

};

#endif // MYSERVERBRIDGE_H
