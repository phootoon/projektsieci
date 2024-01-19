#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QVector>
class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

signals:
    void newMessage(const QByteArray &ba);
    void statusChanged(const QVector<char> &i);
    void showDeathScreen();

public slots:
    void connectToServer(const QString &ip, const quint16 &port);
    void sendMessage(char message);

private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    int numPlayers;
    QTcpSocket _socket;
};

#endif
