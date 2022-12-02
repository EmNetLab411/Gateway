#include "uavlink_msg_setwp_t.h"

uavlink_msg_setwp_t::uavlink_msg_setwp_t(qint64 type, qint64 wpId, float targetX, float targetY,float targetZ, QObject *parent ) :
     QObject(parent), _type(uint16_t(type)), _wpId(uint32_t(wpId)), _targetX(float(targetX)), _targetY(float(targetY)), _targetZ(float(targetZ))
{

}
uavlink_msg_setwp_t::~uavlink_msg_setwp_t()
{

}
QByteArray uavlink_msg_setwp_t::ToPackage()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _type;
    stream << _wpId;
    stream << _targetX;
    stream << _targetY;
    stream << _targetZ;
    return data;
}
