#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client/connect_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void onCloseButtonClicked(); // Add this line
    void onClientButtonClicked();
    void onServerButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
