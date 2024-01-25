#include "Host_window.h"
#include "Server.h"


Host_window::Host_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Host_window){
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &Host_window::onLineEditEditingFinished);
}
Host_window::~Host_window() {
    delete ui;
}

void Host_window::onLineEditEditingFinished(){
    userInputIP = ui->lineEdit->text();
    int numberOfPlayers;
    numberOfPlayers = userInputIP.toInt();
    if (numberOfPlayers<2 && numberOfPlayers>50){
        numberOfPlayers = 20;
    }
    TcpServer *server = new TcpServer(this, numberOfPlayers);
}














