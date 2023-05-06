#include "uavlink_msg_global_position_t.h"
#include <QDebug>

uavlink_msg_global_position_t::uavlink_msg_global_position_t(QObject *parent) : QObject(parent)
{

}

uavlink_msg_global_position_t::~uavlink_msg_global_position_t()
{

}

void uavlink_msg_global_position_t::Decode(QByteArray data)
{
    QDataStream dataStream(data);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    dataStream >> _lat;
    dataStream >> _lon;
    dataStream >> _alt;
    dataStream >> _vx;
    dataStream >> _vy;
    dataStream >> _vz;
    dataStream >> _yaw;
}

qint32 uavlink_msg_global_position_t::getLatitude()
{
    return _lat;
}

qint32 uavlink_msg_global_position_t::getLongitude()
{
    return _lon;
}

qint16 uavlink_msg_global_position_t::getAltitude()
{
    return _alt;
}

qint16 uavlink_msg_global_position_t::getVx()
{
    return _vx;
}

qint16 uavlink_msg_global_position_t::getVy()
{
    return _vy;
}

qint16 uavlink_msg_global_position_t::getVz()
{
    return _vz;
}

qint16 uavlink_msg_global_position_t::getYaw()
{
    return _yaw;
}



void uavlink_msg_global_position_t::setYaw(qint16 newYaw)
{
    if (_yaw == newYaw)
        return;
    _yaw = newYaw;
    emit yawChanged();
}

void uavlink_msg_global_position_t::setVx(qint16 newVx)
{
    if (_vx == newVx)
        return;
    _vx = newVx;
    emit vxChanged();
}

void uavlink_msg_global_position_t::setVy(qint16 newVy)
{
    if (_vy == newVy)
        return;
    _vy = newVy;
    emit vyChanged();
}

void uavlink_msg_global_position_t::setVz(qint16 newVz)
{
    if (_vz == newVz)
        return;
    _vz = newVz;
    emit vzChanged();
}

void uavlink_msg_global_position_t::setLat(qint32 newLat)
{
    if (_lat == newLat)
        return;
    newLat = _lat;
    emit latChanged();
    qDebug() << newLat;
}

void uavlink_msg_global_position_t::setLon(qint32 newLon)
{
    if (_lon == newLon)
        return;
    newLon = _lon;
    emit lonChanged();
    qDebug() << newLon;
}



