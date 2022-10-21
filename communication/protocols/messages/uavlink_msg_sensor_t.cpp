#include "uavlink_msg_sensor_t.h"

uavlink_msg_sensor_t::uavlink_msg_sensor_t(QObject *parent) : QObject(parent)
{

}
uavlink_msg_sensor_t::~uavlink_msg_sensor_t()
{

}

int uavlink_msg_sensor_t::getSensorID()
{
    return _id;
}

float uavlink_msg_sensor_t::getTemp()
{
    return _temp / 100.0f;
}

float uavlink_msg_sensor_t::getHum()
{
    return _hum / 100.0f;
}

float uavlink_msg_sensor_t::getGas()
{
    return _gas / 100.0f;
}

double uavlink_msg_sensor_t::getLat()
{
    return ((double) _lat) / 10000000.0f;
}

double uavlink_msg_sensor_t::getLon()
{
    return ((double) _lon) / 10000000.0f;
}


void uavlink_msg_sensor_t::Decode(QByteArray data)
{
    QDataStream test(data);
    test.setByteOrder(QDataStream::LittleEndian);

    test >> _id;
    test >> _lat;
    test >> _lon;
    test >> _temp;
    test >> _hum;
    test >> _gas;


}


