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
    dataStream >> _rotation;

}

double uavlink_msg_global_position_t::getLatitude()
{
    return ((double) _lat) / 10000000.0f;
}

double uavlink_msg_global_position_t::getLongitude()
{
    return ((double)_lon) / 10000000.0f;
}

float uavlink_msg_global_position_t::getAltitude()
{
    return ((float)_alt) / 100.0f;
}

float uavlink_msg_global_position_t::getVx()
{
    return ((float)_vx) / 100.0f;
}

float uavlink_msg_global_position_t::getVy()
{
    return ((float)_vy) / 100.0f;
}

float uavlink_msg_global_position_t::getVz()
{
    return ((float)_vz) / 100.0f;
}

float uavlink_msg_global_position_t::getRotation()
{
    return (float) _rotation;
}
