#include "Game_window.h"
#include "client/ui_gamewindow.h"
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QPainter>
#include <QKeyEvent>
#include "Client.h"
#include "../server/Game_state.h"

QByteArray serializeInt(int data) {
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << data;

    return byteArray;
}
QVector<bool> deserializeQByteArray(const QByteArray& byteArray)
{
    QVector<bool> result;

    QDataStream stream(byteArray);
    stream.setByteOrder(QDataStream::LittleEndian);

    while (!stream.atEnd())
    {
        bool element;
        stream >> element;
        result.append(element);
    }

    return result;
}


Game_Window::Game_Window(QWidget *parent)
{
    setFixedSize(720, 480);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

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
            Game_Window::Generateenemies(playeramount,aliveStatus);

            emit handleMovement(serializeInt(4));
        }
        break;
    case Qt::Key_Right:
        if(aimplayerindex < playeramount-1){
            aimplayerindex ++;
            Game_Window::Generateenemies(playeramount,aliveStatus);
            emit handleMovement(serializeInt(3));
        }
        break;
    case Qt::Key_Space:
        // Logic for starting shooting
        emit handleMovement(serializeInt(1));
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        // Logic for shooting
        emit handleMovement(serializeInt(3));
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
            QPixmap pixmap(":/ress/resources/aim.png"); // Replace with the correct path
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }else if(aliveStatus[i]==true){
            QPixmap pixmap(":/ress/resources/image.png"); // Replace with the correct path
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }else{
            QPixmap pixmap(":/ress/resources/dead.png"); // Replace with the correct path
            pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
        }



        layout->addWidget(label);
    }

    // Set spacing and add layout to the central widget // Adjust spacing as needed
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
};

void Game_Window::statusChanged(const QByteArray &status){
    QVector<bool> aliveStatus = deserializeQByteArray(status);
    Game_Window::Generateenemies(aliveStatus.size() / 4,aliveStatus);
}


