#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab->setAutoFillBackground(true);

    console = new Console;
    console->setEnabled(true);
    console->setLocalEchoEnabled(true);
    ui->layoutConsole->addWidget(console);

    QPixmap pix(":/resource/icon/Lab_logo.jpg");
    ui->labelLabIcon->setPixmap(pix.scaled(200, 200));



}

MainWindow::~MainWindow()
{
    delete ui;
}

