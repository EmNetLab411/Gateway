#ifndef UAVLINK_MSG_SETWP_T_H
#define UAVLINK_MSG_SETWP_T_H

#include <QObject>
#include <iostream>
#include <QDataStream>
#include <QDebug>

class uavlink_msg_setwp_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_setwp_t(qint64 type, qint64 wpId, float targetX, float targetY,float targetZ, QObject *parent = nullptr);
    ~uavlink_msg_setwp_t();
    QByteArray ToPackage();

signals:
private:
    uint16_t _type;
    uint32_t _wpId;
    float _targetX;
    float _targetY;
    float _targetZ;
};

#endif // UAVLINK_MSG_SETWP_T_H
