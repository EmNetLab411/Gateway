#include "socketudp.h"

socketudp::socketudp(QWidget *parent)
    : QMainWindow(parent)
{
    socket = new QUdpSocket(this);
    lineEdit = new QLineEdit(this);
    socket->bind(QHostAddress::LocalHost, 1234);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readReady()));
    connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(lineText()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::readReady()
{
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

    qDebug() << "Message from: " << sender.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void MainWindow::lineText()
{
    QByteArray data;
    char myChar[1024];

    QString myStr = lineEdit->text();
    memset(myChar, '\0', sizeof(myChar));
    memcpy(myChar, lineEdit->text().toUtf8(), myStr.length());
    data.append(myChar);
    lineEdit->clear();
    socket->writeDatagram(data, QHostAddress::LocalHost, 1234);
}

