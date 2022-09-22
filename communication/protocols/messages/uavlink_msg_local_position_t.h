#ifndef UAVLINK_MSG_LOCAL_POSITION_T_H
#define UAVLINK_MSG_LOCAL_POSITION_T_H

#include <QObject>

class uavlink_msg_local_position_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_local_position_t(QObject *parent = nullptr);

signals:

};

#endif // UAVLINK_MSG_LOCAL_POSITION_T_H
