#include "uavlink_msg_sensor_t.h"

uavlink_msg_sensor_t::uavlink_msg_sensor_t(QObject *parent) : QObject(parent)
{

}

int uavlink_msg_sensor_t::getSensorID()
{
    return _id;
}

float uavlink_msg_sensor_t::getTemp()
{
    return _temp;
}

float uavlink_msg_sensor_t::getHum()
{
    return _hum;
}

float uavlink_msg_sensor_t::getDust()
{
    return _dust;
}

double uavlink_msg_sensor_t::getLat()
{
    return _lat;
}

double uavlink_msg_sensor_t::getLon()
{
    return _lon;
}


void uavlink_msg_sensor_t::Decode(QByteArray data)
{
    _id = data[0];
    _temp = data[1];
    _hum = data[2];
    _dust = data[3];

    qDebug() << data.size();
//    _lat = ((double)data[2, 5]) / 10000000.0f;
//    _lon = ((double)data[6, 9]) / 10000000.0f;
//    _temp = ((float)data[10, 11]) / 100.0f;
//    _hum = ((float)data[12, 13]) / 100.0f;
//    _dust = ((float)data[14, 15]) / 100.0f;

}
