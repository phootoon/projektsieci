#ifndef DEATH_SCREEN_WINDOW_H
#define DEATH_SCREEN_WINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Death_screen; }
QT_END_NAMESPACE

class Death_screen : public QWidget {
    Q_OBJECT

public:
    explicit Death_screen(QWidget *parent = nullptr);
    ~Death_screen();
    void displayRemainingPlayers(int number);

private:
    Ui::Death_screen *ui;
};

#endif // DEATH_SCREEN_WINDOW_H
