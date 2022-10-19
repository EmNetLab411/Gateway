#include "udpclient.h"

Udpclient::Udpclient(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket ->bind(QHostAddress::LocalHost, 54321);
    connect(socket,&QUdpSocket::readyRead,this,&Udpclient::handle_new_msg);
    QByteArray msg = "hello";
    socket->writeDatagram(msg, QHostAddress::LocalHost,12345);
    qDebug()<<"connect";
}

Udpclient::~Udpclient()
{

}
void Udpclient::handle_new_msg()
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
void Udpclient::send_msg(QByteArray msg)
{

}
