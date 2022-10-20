#include "uavlink_msg_control_robot_t.h"

uavlink_msg_control_robot_t::uavlink_msg_control_robot_t(qint64 Step1, qint64 Step2, qint64 Step3, qint64 Step4, qint64 Step5, QObject *parent) :
    QObject(parent), _Step1(qint32(Step1)), _Step2(qint32(Step2)), _Step3(qint32(Step3)), _Step4(qint32(Step4)), _Step5(qint32(Step5))
{

}

uavlink_msg_control_robot_t::~uavlink_msg_control_robot_t()
{

}
QByteArray uavlink_msg_control_robot_t::ToPackage()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << _Step1;
    stream << _Step2;
    stream << _Step3;
    stream << _Step4;
    stream << _Step5;
    return data;
}
