#include "udpclient.h"

udpclient::udpclient(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    client_addr="192.168.0.123";
    socket->connectToHost(QHostAddress(client_addr) , 12345);
    QByteArray msg = "hello";
    int ret = socket->writeDatagram(msg, QHostAddress(client_addr),12345);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&udpclient::send_msg_manual_control);
    connect(socket,&QUdpSocket::readyRead,this,&udpclient::handle_new_msg);
    timer->start(200);
}

udpclient::~udpclient()
{
    qDebug()<<"destroy";
}

//message from  UAV to thingsboard
void udpclient::handle_new_msg()
{
    emit uav_connected();

    while (socket->hasPendingDatagrams()) {
            QNetworkDatagram data = socket->receiveDatagram();
            uavlink_message_t uavlink_msg;
            uavlink_msg.Decode(data.data());
//            qDebug()<<"udpclient new msg udp"<<uavlink_msg.getMessageID();
            switch (uavlink_msg.getMessageID())
            {
                case UAVLINK_MSG_ID_STATE:
                    emit new_msg_state_received(uavlink_msg.getPayLoad());
                    break;
                case UAVLINK_MSG_ID_GLOBAL_POSITION:
                    emit new_msg_global_position_received(uavlink_msg.getPayLoad());
                    break;
                case UAVLINK_MSG_ID_SENSOR:
                    emit new_msg_sensor_received(uavlink_msg.getPayLoad());
                    break;
                default:
                    qDebug()<<"UDP client: unknown uavlink message id";
            }
        }
}

//message from thingsboard to UAV
void udpclient::send_msg_manual_control()
{
    if(_is_new_msg_manual_control)
    {
        uavlink_msg_manual_control_t manual_control_msg(_Vx,_Vy,_Vz,_Yawrate);
        uavlink_message_t msg;
        msg.setMessageId(UAVLINK_MSG_ID_MANUAL_CONTROL);
        msg.setLenPayLoad(UAVLINK_MSG_ID_MANUAL_CONTROL_LEN);
        msg.setPayLoad(manual_control_msg.ToPackage());
        socket->writeDatagram(msg.Encode(), QHostAddress(client_addr),12345);
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
    socket->writeDatagram(msg.Encode(),QHostAddress(client_addr),12345);
}
void udpclient::send_msg_control_robot(qint32 Step1, qint32 Step2, qint32 Step3, qint32 Step4, qint32 Step5)
{
    uavlink_msg_control_robot_t control_robot_msg(Step1, Step2, Step3, Step4, Step5);
    uavlink_message_t msg;
    msg.setMessageId(UAVLINK_MSG_ID_ROBOT_CONTROL);
    msg.setLenPayLoad(UAVLINK_MSG_ID_ROBOT_CONTROL_LEN);
    msg.setPayLoad(control_robot_msg.ToPackage());
    socket->writeDatagram(msg.Encode(),QHostAddress(client_addr),12345);
}
void udpclient::send_msg_waypoint(qint32 waypointId, qint32 lat, qint32 lon, qint32 alt)
{
    uavlink_msg_setwp_t wp_msg(1,waypointId,lat,lon,alt);
    uavlink_message_t msg;
    msg.setMessageId(UAVLINK_MSG_ID_SETWP);
    msg.setLenPayLoad(UAVLINK_MSG_ID_SETWP_LEN);
    msg.setPayLoad(wp_msg.ToPackage());
    socket->writeDatagram(msg.Encode(),QHostAddress(client_addr),12345);
}
