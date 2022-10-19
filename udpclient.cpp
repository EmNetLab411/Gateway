#include "udpclient.h"

udpclient::udpclient(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket ->bind(QHostAddress::LocalHost, 54321);
    connect(socket,&QUdpSocket::readyRead,this,&udpclient::handle_new_msg);
    QByteArray msg = "hello";
    socket->writeDatagram(msg, QHostAddress::LocalHost,12345);
    qDebug()<<"connect";
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&udpclient::send_msg_manual_control);
    timer->start(200);
}

udpclient::~udpclient()
{
    qDebug()<<"destroy";
}
void udpclient::handle_new_msg()
{
    while (socket->hasPendingDatagrams()) {
            QNetworkDatagram data = socket->receiveDatagram();
            uavlink_message_t uavlink_msg;
            uavlink_msg.Decode(data.data());
            switch (uavlink_msg.getMessageID())
            {
                case UAVLINK_MSG_ID_STATE:
                    emit new_msg_state_received(uavlink_msg.getPayLoad());
                    break;
                case UAVLINK_MSG_ID_GLOBAL_POSITION:
                    emit new_msg_global_position_received(uavlink_msg.getPayLoad());
                    break;
                default:
                    qDebug()<<"unknown uavlink message id";
            }
        }
}
void udpclient::send_msg_manual_control()
{
    if(_is_new_msg_manual_control)
    {
        uavlink_msg_manual_control_t manual_control_msg(_Vx,_Vy,_Vz,_Yawrate);
        uavlink_message_t msg;
        msg.setMessageId(UAVLINK_MSG_ID_MANUAL_CONTROL);
        msg.setLenPayLoad(UAVLINK_MSG_ID_MANUAL_CONTROL_LEN);
        msg.setPayLoad(manual_control_msg.ToPackage());
        socket->writeDatagram(msg.Encode(),QHostAddress::LocalHost,12345);
    }
}
void udpclient::hold_manual_control_data(qint32 Vx, qint32 Vy, qint32 Vz, qint32 Yawrate, bool is_new)
{
    _Vx = Vx;
    _Vy = Vy;
    _Vz = Vz;
    _Yawrate = Yawrate;
    _is_new_msg_manual_control = is_new;
}
void udpclient::send_msg_command(qint16 mode_id, float param1, float param2, float param3, float param4)
{
    uavlink_msg_command_t command_msg(mode_id,param1,param2,param3,param4);
    uavlink_message_t msg;
    msg.setMessageId(UAVLINK_MSG_ID_COMMAND);
    msg.setLenPayLoad(UAVLINK_MSG_ID_COMMAND_LEN);
    msg.setPayLoad(command_msg.ToPackage());
    socket->writeDatagram(msg.Encode(),QHostAddress::LocalHost,12345);
}
