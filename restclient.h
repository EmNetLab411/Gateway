#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDateTime>
#include <QJsonArray>
#include <QThread>
#include "communication/protocols/messages/uavlink_msg_manual_control_t.h"
#include "communication/protocols/messages/uavlink_msg_command_t.h"

class restclient : public QObject
{
    Q_OBJECT
public:
    explicit restclient(QObject *parent = nullptr);
    ~restclient();
    QTimer *timer_manual_control;
    QTimer *timer_control_robot;
    QTimer *timer_command;
private:
    QByteArray command_request_url, manual_control_request_url, waypoint_request_url, control_robot_request_url;
    QByteArray command_key, manual_control_key, waypoint_key, control_robot_key;
    int lastest_command_id;
    int Vx, Vy, Vz, Yawrate;
    int Step1, Step2, Step3, Step4, Step5;
    qint16 mode_id;
    float param1, param2, param3, param4;
    QByteArray *command;
    QTime *time_now;
    QNetworkAccessManager *command_receiver;
    QNetworkAccessManager *manual_control_receiver;
    QNetworkAccessManager *waypoint_receiver;
    QNetworkAccessManager *control_robot_receiver;
    QNetworkRequest command_request;
    QNetworkRequest manual_control_request;
    QNetworkRequest waypoint_request;
    QNetworkRequest control_robot_request;
signals:
    void new_command_received(qint16 id, float param1, float param2, float param3, float param4);
    void new_manual_control_received(qint16 vx, qint16 vy, qint16 vz, qint16 yawrate,bool is_new);
    void new_waypoint_received(qint16 waypointId, qint32 lat, qint32 lon, qint32 alt);
    void new_control_robot_received(quint32 step1, quint32 step2, quint32 step3, quint32 step4, quint32 step5);
private slots:
    void read_command();
    void read_manual_control();
    void read_control_robot();
    void handle_command(QNetworkReply *reply);
    void handle_manual_control(QNetworkReply *reply);
    void handle_waypoint(QNetworkReply *reply);
    void handle_control_robot(QNetworkReply *reply);

};

#endif // RESTCLIENT_H
