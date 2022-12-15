#include "uavlink_msg_setwp_t.h"

uavlink_msg_setwp_t::uavlink_msg_setwp_t(qint64 type, qint64 wpId, qint64 targetX, qint64 targetY,qint64 targetZ, QObject *parent ) :
     QObject(parent), _type(uint16_t(type)), _wpId(uint32_t(wpId)), _targetX(int32_t(targetX)), _targetY(int32_t(targetY)), _targetZ(int32_t(targetZ))
{

}
uavlink_msg_setwp_t::~uavlink_msg_setwp_t()
{

}
QByteArray uavlink_msg_setwp_t::ToPackage()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _type;
    stream << _wpId;
    stream << (float(_targetX)/10000000);
    stream << (float(_targetY)/10000000);
    stream << float(_targetZ);
    return data;
}
