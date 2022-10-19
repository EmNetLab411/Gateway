#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include<QObject>
#include<QUdpSocket>
#include <QNetworkDatagram>
#include "communication/protocols/uavlink_message_t.h"

class Udpclient : public QObject
{
    Q_OBJECT
public:
    explicit Udpclient(QObject *parent = nullptr);
    ~Udpclient();
private:
    QUdpSocket *socket;
signals:
    void new_msg_state_received(QByteArray msg);
    void new_msg_global_position_received(QByteArray msg);
public slots:
    void handle_new_msg();
    void send_msg(QByteArray msg);
};

#endif // UDPCLIENT_H
