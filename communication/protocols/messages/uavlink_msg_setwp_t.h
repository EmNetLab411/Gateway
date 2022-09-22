#ifndef UAVLINK_MSG_SETWP_T_H
#define UAVLINK_MSG_SETWP_T_H

#include <QObject>

class uavlink_msg_setwp_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_setwp_t(QObject *parent = nullptr);

signals:

};

#endif // UAVLINK_MSG_SETWP_T_H
