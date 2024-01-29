#include <QMainWindow>
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "Death_screen.h"


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
    int aimplayerindex;
    QVector<bool> aliveStatus;
    void Generateenemies(int numberofplayers, QVector<bool> alivearray);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    signals:
        void _disconnect();
        void handleMovement(const char keyPressed);

public slots:
    void statusChanged(const QVector<char> &i);
    void showDeathScreen();


private:
    void closeEvent(QCloseEvent *event) override;
    Ui::Game_Window *ui;
};


#endif // GAME_WINDOW_H

