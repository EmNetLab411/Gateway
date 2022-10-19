#ifndef UAVLINK_MSG_COMMAND_T_H
#define UAVLINK_MSG_COMMAND_T_H
#include <QObject>
#include <iostream>
#include <QDataStream>
#include <QDebug>
class uavlink_msg_command_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_command_t(qint64 Mode_Id, float Param1, float Param2, float Param3, float Param4, QObject *parent = nullptr);
    ~uavlink_msg_command_t();
    QByteArray ToPackage();
private:
    qint16 _Mode_Id ;
    float _Param1;
    float _Param2;
    float _Param3;
    float _Param4;
};

#endif // UAVLINK_MSG_COMMAND_T_H
