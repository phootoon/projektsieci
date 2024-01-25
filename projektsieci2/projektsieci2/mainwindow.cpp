#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client/connect_window.h"
#include "server/Host_window.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    connect(ui->PushButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->client, &QPushButton::clicked, this, &MainWindow::onClientButtonClicked);
    connect(ui->server, &QPushButton::clicked, this, &MainWindow::onServerButtonClicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    this->close();
}
void MainWindow::onClientButtonClicked(){
    Connect_window *connectWindow = new Connect_window(this);
    connectWindow->setAttribute(Qt::WA_DeleteOnClose);
    connectWindow->show();
}
void MainWindow::onServerButtonClicked(){
    Host_window *hostWindow = new Host_window(this);
    hostWindow->setAttribute(Qt::WA_DeleteOnClose);
    hostWindow->show();
}

