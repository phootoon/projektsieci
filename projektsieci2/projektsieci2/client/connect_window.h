#ifndef CONNECT_WINDOW_H
#define CONNECT_WINDOW_H
#include <QWidget>
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Connect_window; }
QT_END_NAMESPACE
class Connect_window: public QWidget {
    Q_OBJECT

public:
    explicit Connect_window(QWidget *parent = nullptr);
    ~Connect_window();
    QString userInputIP;
    QString userInputPort;
    bool isValidIPAddress(const QString& ip);
    TcpClient *tcpclient;

public slots:
    void onLineEditEditingFinished();
    void onLineEditingPortFinished();

private:
    Ui::Connect_window *ui;
};

#endif // CONNECT_WINDOW_H




