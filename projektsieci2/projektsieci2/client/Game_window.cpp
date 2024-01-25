#include "Game_window.h"

#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QKeyEvent>

QVector<bool> convertToBoolVector(const QVector<char> &charVector) {
    QVector<bool> boolVector;

    for (char ch : charVector) {
        boolVector.append(static_cast<bool>(ch));
    }

    return boolVector;
}

Game_Window::Game_Window(QWidget *parent)
{
    setFixedSize(720, 480);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    int aimplayerindex = 0;
}




Game_Window::~Game_Window()
{
    delete ui;
}

void Game_Window::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/ress/resources/gamewindowbackground.jpg");
    painter.drawPixmap(0, 0, width(), height(), background);
}
void Game_Window::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        if((aimplayerindex > 0) && (aimplayerindex < aliveStatus.size())){
            aimplayerindex --;
            qInfo() << aimplayerindex << "aimleft";
            Game_Window::Generateenemies(aliveStatus.size(),aliveStatus);

            emit handleMovement('4');
        }
        break;
    case Qt::Key_Right:
        qInfo() << aimplayerindex;
        qInfo() << aliveStatus.size();
        if((aimplayerindex < aliveStatus.size() - 1) && (aimplayerindex >= 0)){
            aimplayerindex ++;
            qInfo() << aimplayerindex << "aimright";
            Game_Window::Generateenemies(aliveStatus.size(),aliveStatus);
            emit handleMovement('3');
        }
        break;
    case Qt::Key_Space:
        // Logic for starting shooting
        emit handleMovement('1');
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        // Logic for shooting
        emit handleMovement('2');
        break;
    default:
        QMainWindow::keyPressEvent(event); // Make sure to call the base class implementation
    }
}


void Game_Window::Generateenemies(int numberofplayers,QVector<bool> aliveStatus)
{
    // std::vector<bool> aliveStatus(20, false);
    QHBoxLayout *layout = new QHBoxLayout;
    int imagesize = round(500/numberofplayers);
    for (int i = 0; i < numberofplayers; ++i) {
        QLabel *label = new QLabel(this);

        if (i==aimplayerindex){
            if (aliveStatus[i] == true){
                QPixmap pixmap(":/ress/resources/aim.png");
                pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label->setPixmap(pixmap);
            }
            else{
                QPixmap pixmap(":/ress/resources/dead_aimed.png");
                pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                label->setPixmap(pixmap);
            }
        }else if(aliveStatus[i]==true){
            QPixmap pixmap(":/ress/resources/image.png");
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }else{
            QPixmap pixmap(":/ress/resources/dead.png");
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }



        layout->addWidget(label);
    }
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
};

void Game_Window::statusChanged(const QVector<char> &status){
    qInfo() << "statusChanged";
    aliveStatus = convertToBoolVector(status);
    Game_Window::Generateenemies(aliveStatus.size(), aliveStatus);
}

void Game_Window::showDeathScreen(){
    aimplayerindex = -1;
    Death_screen *death_screen = new Death_screen(this);
    death_screen->show();
}
