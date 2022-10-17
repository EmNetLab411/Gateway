#ifndef SOCKETUDP_H
#define SOCKETUDP_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QLineEdit>

class socketudp : public QMainWindow
{
    Q_OBJECT

public:
    socketudp(QWidget *parent = nullptr);
    ~socketudp();

public slots:
    void readReady();
    void lineText();

private:
    QUdpSocket *socket;
    QLineEdit *lineEdit;
};
#endif // SOCKETUDP_H