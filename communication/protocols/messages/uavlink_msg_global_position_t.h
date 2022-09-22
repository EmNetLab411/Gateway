#ifndef UAVLINK_MSG_GLOBAL_POSITION_T_H
#define UAVLINK_MSG_GLOBAL_POSITION_T_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>

class uavlink_msg_global_position_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_global_position_t(QObject *parent = nullptr);
    ~uavlink_msg_global_position_t();

    void Decode(QByteArray data);
    double getLatitude();
    double getLongitude();
    float getAltitude();
    float getVx();
    float getVy();
    float getVz();
    float getRotation();
signals:

private:
    qint64 _lat;
    qint64 _lon;
    qint32 _alt;
    qint32 _vx;
    qint32 _vy;
    qint32 _vz;
    qint32 _rotation;
};

#endif // UAVLINK_MSG_GLOBAL_POSITION_T_H
