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
    explicit uavlink_msg_setwp_t(qint64 type, qint64 wpId, qint64 targetX, qint64 targetY,qint64 targetZ, QObject *parent = nullptr);
    ~uavlink_msg_setwp_t();
    QByteArray ToPackage();

signals:
private:
    uint16_t _type;
    uint32_t _wpId;
    int32_t _targetX;
    int32_t _targetY;
    int32_t _targetZ;
};

#endif // UAVLINK_MSG_SETWP_T_H
