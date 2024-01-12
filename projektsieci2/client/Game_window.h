#include <QMainWindow>
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

QT_BEGIN_NAMESPACE
namespace Ui { class Game_Window; }
QT_END_NAMESPACE

class Game_Window : public QMainWindow
{
    Q_OBJECT
public:
    Game_Window(QWidget *parent = nullptr);
    ~Game_Window();
    QString ip;
    int playeramount;
    void Generateenemies(int numberofplayers);


signals:
    void buttonPressed(int value);

public slots:
    void onRightButtonClicked();
    void onLeftButtonClicked();
    void onShootButtonClicked();
    void onExitButtonClicked();
    void onAimButtonClicked();

private:
    Ui::Game_Window *ui;
};


#endif // GAME_WINDOW_H

