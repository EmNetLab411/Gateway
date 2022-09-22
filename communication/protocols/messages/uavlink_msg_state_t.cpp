#include "uavlink_msg_state_t.h"

uavlink_msg_state_t::uavlink_msg_state_t(QObject *parent) : QObject(parent)
{

}

uavlink_msg_state_t::~uavlink_msg_state_t()
{

}

void uavlink_msg_state_t::Decode(QByteArray data)
{
    QDataStream test(data);
    test.setByteOrder(QDataStream::LittleEndian);

    test >> _connected;
    test >> _armed;
    test >> _mode;
    test >> _batterty;
}
