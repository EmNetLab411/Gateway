#include "uavlink_msg_command_t.h"

uavlink_msg_command_t::uavlink_msg_command_t(qint64 Mode_Id, float Param1, float Param2, float Param3, float Param4, QObject *parent):
    QObject(parent), _Mode_Id(qint16(Mode_Id)), _Param1(Param1), _Param2(Param2), _Param3(Param3), _Param4(Param4)
{

}
uavlink_msg_command_t::~uavlink_msg_command_t()
{

}
QByteArray uavlink_msg_command_t::ToPackage()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setFloatingPointPrecision(QDataStream::SinglePrecision); // dat float use 32bit
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _Mode_Id;
    stream << _Param1;
    stream << _Param2;
    stream << _Param2;
    stream << _Param4;
    qDebug() << data.length();
    return data;
}
