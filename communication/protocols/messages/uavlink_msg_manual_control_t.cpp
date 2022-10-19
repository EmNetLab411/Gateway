#include "uavlink_msg_manual_control_t.h"

uavlink_msg_manual_control_t::uavlink_msg_manual_control_t(qint64 Vx, qint64 Vy, qint64 Vz, qint64 Yawrate, QObject *parent) :
    QObject(parent), _Vx(qint32(Vx)), _Vy(qint32(Vy)), _Vz(qint32(Vz)), _Yawrate(qint32(Yawrate))
{

}
uavlink_msg_manual_control_t::~uavlink_msg_manual_control_t()
{

}
QByteArray uavlink_msg_manual_control_t::ToPackage()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _Vx;
    stream << _Vy;
    stream << _Vz;
    stream << _Yawrate;
    return data;
}
