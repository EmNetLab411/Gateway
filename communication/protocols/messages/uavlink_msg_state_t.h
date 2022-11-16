#ifndef UAVLINK_MSG_STATE_T_H
#define UAVLINK_MSG_STATE_T_H

#include <QObject>
#include <QByteRef>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
class uavlink_msg_state_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_state_t(QObject *parent = nullptr);
    ~uavlink_msg_state_t();
    void Decode(QByteArray data);
    int getConnected();
    int getArmed();
    int getMode();
    int getBattery();

signals:

private:
    qint8 _connected;
    qint8 _armed;
    qint8 _mode;
    qint8 _batterty;

};

#endif // UAVLINK_MSG_STATE_T_H
