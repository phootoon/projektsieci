#ifndef HOST_H
#define HOST_H

QT_BEGIN_NAMESPACE
namespace Ui { class Host_window; }
QT_END_NAMESPACE

class Host
{
public:
    Host();
};

#endif // HOST_H





#ifndef CONNECT_WINDOW_H
#define CONNECT_WINDOW_H
#include <QWidget>

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

public slots:
    void onLineEditEditingFinished();
    void onLineEditingPortFinished();

private:
    Ui::Connect_window *ui;
};

#endif // CONNECT_WINDOW_H




