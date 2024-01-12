#include "Game_window.h"
#include "client/ui_gamewindow.h"
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QKeyEvent>
#include "Client.h"
#include "../server/Game_state.h"


Game_Window::Game_Window(QWidget *parent)
{
    setFixedSize(720, 480);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    Generateenemies(playeramount);
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
        if(aimplayerindex > 0){
            aimplayerindex --;
            Game_Window::Generateenemies(playeramount);
        }
        break;
    case Qt::Key_Right:
        if(aimplayerindex < playeramount-1){
            aimplayerindex ++;
            Game_Window::Generateenemies(playeramount);
        }
        break;
    case Qt::Key_Space:
        // Logic for starting shooting
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        // Logic for shooting
        break;
    default:
        QMainWindow::keyPressEvent(event); // Make sure to call the base class implementation
    }
}


void Game_Window::Generateenemies(int numberofplayers)
{
    QHBoxLayout *layout = new QHBoxLayout;
    int imagesize = round(800/numberofplayers);
    for (int i = 0; i < numberofplayers; ++i) {
        QLabel *label = new QLabel(this);
        if (i==aimplayerindex){
            QPixmap pixmap(":/ress/resources/aim.png"); // Replace with the correct path
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }else{
            QPixmap pixmap(":/ress/resources/image.png"); // Replace with the correct path
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        };



        layout->addWidget(label);
    }

    // Set spacing and add layout to the central widget // Adjust spacing as needed
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
};


