#ifndef UAVLINK_MSG_GLOBAL_POSITION_T_H
#define UAVLINK_MSG_GLOBAL_POSITION_T_H

#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QObject>

class uavlink_msg_global_position_t : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 newLat READ getLatitude WRITE setLat NOTIFY latChanged)
    Q_PROPERTY(qint32 newLon READ getLongitude WRITE setLon NOTIFY lonChanged)
    Q_PROPERTY(qint16 newYaw READ getYaw WRITE setYaw NOTIFY yawChanged)
    Q_PROPERTY(qint16 newVx READ getVx WRITE setVx NOTIFY vxChanged)
    Q_PROPERTY(qint16 newVy READ getVy WRITE setVy NOTIFY vyChanged)
    Q_PROPERTY(qint16 newVz READ getVz WRITE setVz NOTIFY vzChanged)
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

    void setLat(qint32 newLat);

    void setLon(qint32 newLon);

    void setYaw(qint16 newYaw);

    void setVx(qint16 newVx);

    void setVy(qint16 newVy);

    void setVz(qint16 newVz);

signals:

    void yawChanged();

    void vxChanged();

    void vyChanged();

    void vzChanged();

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
