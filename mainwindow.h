#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "console.h"
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Console *console;
};
#endif // MAINWINDOW_H
