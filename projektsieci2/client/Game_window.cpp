#include "Game_window.h"
#include "client/ui_gamewindow.h"
#include <QLabel>
#include <QPixmap>
#include "Client.h"

Game_Window::Game_Window(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::Game_Window)
{
    ui->setupUi(this);
    connect(ui->rightaim, &QPushButton::clicked, this, &Game_Window::onRightButtonClicked);
    connect(ui->leftaim, &QPushButton::clicked, this, &Game_Window::onLeftButtonClicked);
    connect(ui->shoot, &QPushButton::clicked, this, &Game_Window::onShootButtonClicked);
    connect(ui->aim, &QPushButton::clicked, this, &Game_Window::onAimButtonClicked);
    connect(ui->exit, &QPushButton::clicked, this, &Game_Window::onExitButtonClicked);
}


Game_Window::~Game_Window()
{
    delete ui;
}

void Game_Window::onShootButtonClicked(){
    emit buttonPressed(1);
}
void Game_Window::onAimButtonClicked(){
    emit buttonPressed(2);
}
void Game_Window::onRightButtonClicked() {
    emit buttonPressed(3);
}
void Game_Window::onLeftButtonClicked(){
    emit buttonPressed(4);
}
void Game_Window::onExitButtonClicked(){
    emit buttonPressed(9);
}
void Game_Window::Generateenemies(int numberofplayers)
{
    QHBoxLayout *layout = new QHBoxLayout;
    int imagesize = round(800/numberofplayers);
    for (int i = 0; i < numberofplayers; ++i) {
        QLabel *label = new QLabel(this);
        QPixmap pixmap(":/ress/resources/image.png"); // Replace with the correct path
        pixmap = pixmap.scaled(imagesize, imagesize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(pixmap);

        layout->addWidget(label);
    }

    // Set spacing and add layout to the central widget // Adjust spacing as needed
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
};


