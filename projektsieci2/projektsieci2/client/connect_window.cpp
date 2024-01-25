#include "connect_window.h"
#include "client/ui_connectwindow.h"
#include "Game_window.h"
#include "Client.h"
#include <qstring.h>
#include <QRegularExpression>



Connect_window::Connect_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Connect_window) {
    ui->setupUi(this);
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
    userInputIP = ui->lineEdit->text();
    userInputPort = ui->linePort->text();
    bool conversionOK;
    quint16 port = userInputPort.toUInt(&conversionOK);

    if (conversionOK) {
        qDebug() << "Port: " << port;
    } else {
        qDebug() << "Invalid port input!";
    }
    TcpClient *tcpclient = new TcpClient(this);
    tcpclient->connectToServer(userInputIP, port);
    Game_Window *gameWindow = new Game_Window(this);
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(gameWindow, &Game_Window::handleMovement, tcpclient, &TcpClient::sendMessage);
    connect(tcpclient, &TcpClient::statusChanged, gameWindow, &Game_Window::statusChanged);
    connect(tcpclient, &TcpClient::showDeathScreen, gameWindow, &Game_Window::showDeathScreen);
    gameWindow->show();
};




