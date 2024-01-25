#include "Host.h"

Host::Host() {}






#include "connect_window.h"
#include "client/ui_connectwindow.h"
#include "Game_window.h"
#include "Client.h"
#include <qstring.h>
#include <QRegularExpression>


Connect_window::Connect_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Connect_window) {
    ui->setupUi(this); // Display 4 on the LCD when the window is created
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &Connect_window::onLineEditEditingFinished);
    connect(ui->linePort, &QLineEdit::editingFinished, this, &Connect_window::onLineEditingPortFinished);
}

Connect_window::~Connect_window() {
    delete ui;
}

void Connect_window::onLineEditEditingFinished(){
    userInputIP = ui->lineEdit->text();
}

void Connect_window::onLineEditingPortFinished(){

    TcpClient *tcpclient = new TcpClient(this);
    userInputIP = ui->lineEdit->text();
    userInputPort = ui->linePort->text();
    quint16 port  = userInputPort.toUShort();
    // if(tcpclient->tryConnectToServer(userInputIP,port,3000)){
    // tryConnectToServer(userInputIP,port, 150)
    Game_Window *gameWindow = new Game_Window(this);
    gameWindow->playeramount = 20;
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Game_Window(gameWindow).ip = userInputIP;
    // Show the Connect_window
    // gameWindow->Generateenemies(30);
    gameWindow->show();
    TcpClient(tcpclient).connectToServer(userInputIP,userInputPort);
    // }
};










