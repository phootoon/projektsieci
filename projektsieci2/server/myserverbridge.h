#ifndef MYSERVERBRIDGE_H
#define MYSERVERBRIDGE_H

#include <QObject>

class MyServerBridge : public QObject
{
    Q_OBJECT
public:
    explicit MyServerBridge(QObject* parent = nullptr);
    void onNewConnection();
    void onReadyRead(int i);

signals:
    void newConnection();
    void readyRead(int i);

};

#endif // MYSERVERBRIDGE_H
