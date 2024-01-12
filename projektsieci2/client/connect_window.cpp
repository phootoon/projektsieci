#include "connect_window.h"
#include "client/ui_connectwindow.h"
#include "Game_window.h"
#include <qstring.h>

Connect_window::Connect_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::Connect_window) {
    ui->setupUi(this); // Display 4 on the LCD when the window is created
    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &Connect_window::onLineEditEditingFinished);

}

Connect_window::~Connect_window() {
    delete ui;
}

void Connect_window::onLineEditEditingFinished(){
    QString userInput = ui->lineEdit->text();
    Game_Window *gameWindow = new Game_Window(this); // Create a new Connect_window
    gameWindow->setAttribute(Qt::WA_DeleteOnClose); // Ensure it's deleted once closed
    Game_Window(gameWindow).ip = userInput;
     // Show the Connect_window
    // gameWindow->Generateenemies(30);
    gameWindow->show();
}






