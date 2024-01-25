#include "Lobby_window.h"
#include "client/ui_lobbywindow.h"

Lobby_Window::Lobby_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Lobby_Window)

{
    ui->setupUi(this);
    connect(ui->ready_up, &QPushButton::clicked, this, &Lobby_Window::onReadyButtonClicked);
    connect(ui->start_early, &QPushButton::clicked, this, &Lobby_Window::onEarlyButtonClicked);

}

Lobby_Window::~Lobby_Window()
{
    delete ui;
}

void Lobby_Window::onReadyButtonClicked(){
    emit buttonPressed(5);
}
void Lobby_Window::onEarlyButtonClicked(){
    emit buttonPressed(6);
}

void Lobby_Window::showCurrentPlayers(int number) {
    ui->lcdCurrentPlayers->display(number);
}

void Lobby_Window::showReadyPlayers(int number) {
    ui->lcdReadyPlayers->display(number);
}
