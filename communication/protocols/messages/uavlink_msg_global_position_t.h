#ifndef UAVLINK_MSG_GLOBAL_POSITION_T_H
#define UAVLINK_MSG_GLOBAL_POSITION_T_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QObject>

class uavlink_msg_global_position_t : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 lat READ lat WRITE setLat NOTIFY latChanged)
    Q_PROPERTY(qint32 lon READ lon WRITE setLon NOTIFY lonChanged)
public:
    explicit uavlink_msg_global_position_t(QObject *parent = nullptr);
    ~uavlink_msg_global_position_t();

    void Decode(QByteArray data);
    qint32 getLatitude();
    qint32 getLongitude();
    qint16 getAltitude();
    qint16 getVx();
    qint16 getVy();
    qint16 getVz();
    qint16 getYaw();

    qint32 lat() const;
    void setLat(qint32 newLat);

    qint32 lon() const;
    void setLon(qint32 newLon);

signals:
    void latChanged();

    void lonChanged();

private:
    qint32 _lat;
    qint32 _lon;
    qint16 _alt;
    qint16 _vx;
    qint16 _vy;
    qint16 _vz;
    qint16 _yaw;

};

#endif // UAVLINK_MSG_GLOBAL_POSITION_T_H
