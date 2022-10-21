#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include<QObject>
#include<QUdpSocket>
#include <QNetworkDatagram>
#include "communication/protocols/uavlink_message_t.h"
#include "communication/protocols/messages/uavlink_msg_manual_control_t.h"
#include "communication/protocols/messages/uavlink_msg_command_t.h"
#include "communication/protocols/messages/uavlink_msg_control_robot_t.h"
#include <QTimer>

class udpclient : public QObject
{
    Q_OBJECT
public:
    explicit udpclient(QObject *parent = nullptr);
    ~udpclient();
    void send_msg_manual_control();
    QTimer *timer;
private:
    qint32 _Vx,_Vy,_Vz,_Yawrate;
    bool _is_new_msg_manual_control;
    QUdpSocket *socket;
signals:
    void new_msg_state_received(QByteArray msg);
    void new_msg_global_position_received(QByteArray msg);
    void new_msg_sensor_received(QByteArray msg);
public slots:
    void handle_new_msg();
    void hold_manual_control_data(qint32 Vx, qint32 Vy, qint32 Vz, qint32 Yawrate, bool is_new);
    void send_msg_command(qint16 mode_id, float param1, float param2, float param3, float param4);
    void send_msg_control_robot(qint32 Step1, qint32 Step2, qint32 Step3, qint32 Step4, qint32 Step5);
};

#endif // UDPCLIENT_H
