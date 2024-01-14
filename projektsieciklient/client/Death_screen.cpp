#include "Death_screen.h"
#include "client/ui_Death_screen.h"


Death_screen::Death_screen(QWidget *parent)
    : QWidget(parent), ui(new Ui::Death_screen) {
    ui->setupUi(this);
    displayRemainingPlayers(4); // Display 4 on the LCD when the window is created
}

Death_screen::~Death_screen() {
    delete ui;
}


void Death_screen::displayRemainingPlayers(int number) {
    ui->lcdRemainingPlayers->display(number);
}








// #include "mainwindow.h"
// #include "ui_mainwindow.h"

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     // Assuming your button is named pushButton in the ui file
//     connect(ui->PushButton, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);
//     connect(ui->client, &QPushButton::clicked, this, &MainWindow::onClientButtonClicked);
//     connect(ui->server, &QPushButton::clicked, this, &MainWindow::onServerButtonClicked);



// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

// void MainWindow::onCloseButtonClicked() {
//     this->close(); // This will close the application
// }
// void MainWindow::onClientButtonClicked(){
//     this->close();
// }
// void MainWindow::onServerButtonClicked(){
//     this->close();
// }
