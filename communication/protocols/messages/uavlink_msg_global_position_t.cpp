#include "uavlink_msg_global_position_t.h"

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
