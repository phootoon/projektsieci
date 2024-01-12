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
public slots:
    void onLineEditEditingFinished();

private:
    Ui::Connect_window *ui;
};

#endif // CONNECT_WINDOW_H




