#ifndef UAVLINK_MSG_MANUAL_CONTROL_T_H
#define UAVLINK_MSG_MANUAL_CONTROL_T_H

#include <QObject>
#include <iostream>
#include <QDataStream>

class uavlink_msg_manual_control_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_manual_control_t(qint64 Vx, qint64 Vy, qint64 Vz, qint64 Yawrate, QObject *parent = nullptr);
    ~uavlink_msg_manual_control_t();
    QByteArray ToPackage();

signals:

private:
    qint32 _Vx;
    qint32 _Vy;
    qint32 _Vz;
    qint32 _Yawrate;

};
#endif // UAVLINK_MSG_MANUAL_CONTROL_T_H
