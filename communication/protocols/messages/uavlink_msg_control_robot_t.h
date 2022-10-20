#ifndef UAVLINK_MSG_CONTROL_ROBOT_T_H
#define UAVLINK_MSG_CONTROL_ROBOT_T_H


#include <QObject>
#include <iostream>
#include <QDataStream>
#include <QDebug>

class uavlink_msg_control_robot_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_control_robot_t(qint64 Step1, qint64 Step2, qint64 Step3, qint64 Step4, qint64 Step5, QObject *parent = nullptr);
    ~uavlink_msg_control_robot_t();
    QByteArray ToPackage();

signals:

private:
    qint32 _Step1;
    qint32 _Step2;
    qint32 _Step3;
    qint32 _Step4;
    qint32 _Step5;

};
#endif // UAVLINK_MSG_CONTROL_ROBOT_T_H
