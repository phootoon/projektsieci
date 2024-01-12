#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client/connect_window.h"
#include "server/Host_window.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    // Assuming your button is named pushButton in the ui file
    connect(ui->PushButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
    connect(ui->client, &QPushButton::clicked, this, &MainWindow::onClientButtonClicked);
    connect(ui->server, &QPushButton::clicked, this, &MainWindow::onServerButtonClicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    this->close(); // This will close the application
}
void MainWindow::onClientButtonClicked(){
    Connect_window *connectWindow = new Connect_window(this); // Create a new Connect_window
    connectWindow->setAttribute(Qt::WA_DeleteOnClose); // Ensure it's deleted once closed
    connectWindow->show(); // Show the Connect_window
    // this->hide();
}
void MainWindow::onServerButtonClicked(){
    Host_window *hostWindow = new Host_window(this);
    hostWindow->setAttribute(Qt::WA_DeleteOnClose);
    hostWindow->show();
}

