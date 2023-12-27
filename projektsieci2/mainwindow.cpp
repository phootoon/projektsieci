#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Assuming your button is named pushButton in the ui file
    connect(ui->PushButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCloseButtonClicked() {
    this->close(); // This will close the application
}
