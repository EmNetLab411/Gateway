#include "uavlink_message_t.h"

uavlink_message_t::uavlink_message_t(QObject *parent) : QObject(parent)
{

}

void uavlink_message_t::setMessageId(MessageID msgid)
{
    _msgID = msgid;
}

void uavlink_message_t::setLenPayLoad(MessageLength lenPayload)
{
    _lenPayload = lenPayload;
}

void uavlink_message_t::setPayLoad(QByteArray payload)
{
    _payload = payload;
}

MessageID uavlink_message_t::getMessageID()
{
    return _msgID;
}

quint8 uavlink_message_t::getLenPayLoad()
{
    return _lenPayload;
}

QByteArray uavlink_message_t::getPayLoad()
{
    return _payload;
}

QByteArray uavlink_message_t::Encode()
{
    QByteArray data;
    data[0] = (qint8)_msgID;
    data[1] = (qint8)_lenPayload;
    data.append(_payload);
    return data;
}

void uavlink_message_t::Decode(QByteArray data)
{
    _msgID = MessageID((qint8) data[0]);
    _lenPayload = (qint8) data[1];
    _payload = data.mid(2,  _lenPayload + 1);
}
