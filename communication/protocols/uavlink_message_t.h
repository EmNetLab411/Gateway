#ifndef UAVLINK_MESSAGE_T_H
#define UAVLINK_MESSAGE_T_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include "messages/messageID.h"

class uavlink_message_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_message_t(QObject *parent = nullptr);

    void setMessageId(MessageID msgid);
    void setLenPayLoad(quint8 lenPayload);
    void setPayLoad(QByteArray payload);
    void Decode(QByteArray data);

    MessageID getMessageID();
    quint8 getLenPlayLoad();
    QByteArray getPayLoad();

    QByteArray Encode();

signals:

private:
    MessageID _msgID;
    quint8 _lenPayload;
    QByteArray _payload;


};

#endif // UAVLINK_MESSAGE_T_H
