#ifndef HOST_WINDOW_H
#define HOST_WINDOW_H
#include "server/ui_hostwindow.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Host_window; }
QT_END_NAMESPACE

class Host_window:public QWidget
{
    Q_OBJECT
public:
    explicit Host_window(QWidget *parent = nullptr);
    ~Host_window();
    QString userInputIP;
public slots:
    void onLineEditEditingFinished();

private:
    Ui::Host_window *ui;
};

#endif // HOST_WINDOW_H







