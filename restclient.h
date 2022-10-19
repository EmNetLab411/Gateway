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
#include "communication/protocols/messages/uavlink_msg_manual_control_t.h"
#include "communication/protocols/messages/uavlink_msg_command_t.h"

class restclient : public QObject
{
    Q_OBJECT
public:
    explicit restclient(QObject *parent = nullptr);
    ~restclient();
    QTimer *timer;
private:
    QByteArray command_request_url, manual_control_request_url, waypoint_request_url, control_robot_request_url;
    QByteArray command_key, manual_control_key, waypoint_key, control_robot_key;
    int lastest_command_id;
    int Vx, Vy, Vz, Yawrate, mode_id;
    float param1, param2, param3, param4;
    QByteArray *command;
    QTime *time_now;
    QNetworkAccessManager *command_receiver;
    QNetworkAccessManager *manual_control_receiver;
    QNetworkAccessManager waypoint_receiver;
    QNetworkAccessManager control_robot_receiver;
    QNetworkRequest command_request;
    QNetworkRequest manual_control_request;
    QNetworkRequest waypoint_request;
    QNetworkRequest control_robot_request;
signals:
    void new_command_received(qint16 id, float param1, float param2, float param3, float param4);
    void new_manual_control_received(qint16 vx, qint16 vy, qint16 vz, qint16 yawrate);
    void new_waypoint_received(qint16 waypointId, qint32 lat, qint32 lon, qint32 alt);
    void control_robot_received(quint16 step1, quint16 step2, quint16 step3, quint16 step4, quint16 step5);
private slots:
    void read_command();
    void read_manual_control();
    void handle_command(QNetworkReply *reply);
    void handle_manual_control(QNetworkReply *reply);
    void handle_waypoint(QNetworkReply *reply);
    void handle_control_robot(QNetworkReply *reply);

};

#endif // RESTCLIENT_H
