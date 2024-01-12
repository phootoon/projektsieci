#include <QMainWindow>

#ifndef LOBBY_WINDOW_H
#define LOBBY_WINDOW_H


QT_BEGIN_NAMESPACE
namespace Ui { class Lobby_Window; }
QT_END_NAMESPACE

class Lobby_Window : public QMainWindow
{
    Q_OBJECT
public:
    Lobby_Window(QWidget *parent = nullptr);
    ~Lobby_Window();
    void showCurrentPlayers(int number);
    void showReadyPlayers(int number);

signals:
    void buttonPressed(int value);

public slots:
    void onReadyButtonClicked();
    void onEarlyButtonClicked();
private:
    Ui::Lobby_Window *ui;
};

#endif // LOBBY_WINDOW_H
