#include "serialport.h"

serialport::serialport(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    PortSettings portSettings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(configFile.LORA_PORT_DEFAULT, portSettings, QextSerialPort::Polling);
    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();

    connect(timer, &QTimer::timeout, this, &serialport::readData);
    connect(port, &QextSerialPort::readyRead, this, &serialport::readData);

    buffer = new QByteArray();

    timer->start(configFile.SERIAL_READ_SPEED_T);

}

serialport::~serialport()
{
    delete buffer;
    delete timer;
    delete port;
}

void serialport::requestOpenSerialPort()
{
    emit signalOpenSerialPort(QThread::NormalPriority);
}

void serialport::openSerialPort()
{
    if(!port->isOpen())  port->open(QIODevice::ReadWrite);

    if(port->isOpen() && port->queryMode() == QextSerialPort::Polling)
    {
        timer->start();
    }
    else
    {
        timer->stop();
    }

}

void serialport::writeData(QByteArray sendData)
{
    port->write(sendData);
}

void serialport::readData()
{
    if(port->bytesAvailable())
    {
        QByteArray receivedByteData = port->readAll();
        if(!receivedByteData.isEmpty())
        {
            buffer->append(receivedByteData);
            qDebug() <<  "buffer size: " << buffer->size();
            int endMessagePosition = buffer->indexOf(":", 0);

            if(!buffer->isEmpty())
            {
                QByteArray messageByteArray = buffer->mid(0, endMessagePosition + 1);
                buffer->remove(0, endMessagePosition + 1);
                uavlink_message_t* message = new uavlink_message_t();
                message->Decode(messageByteArray);

                qDebug() << "msgID: " << message->getMessageID();
                qDebug() << "lenPayload: " << message->getLenPlayLoad();
                qDebug() << "MessageSize" << messageByteArray.size();

                switch (message->getMessageID())
                {
                case UAVLINK_MSG_ID_SENSOR:
                {
                    uavlink_msg_sensor_t* messageSensor = new uavlink_msg_sensor_t();
                    messageSensor->Decode(message->getPayLoad());
                    emit signalReceivedData( messageSensor->getSensorID(),
                                             messageSensor->getLat(),
                                             messageSensor->getLon(),
                                             messageSensor->getTemp(),
                                             messageSensor->getHum(),
                                             messageSensor->getDust());

                    delete messageSensor;
                    break;
                }
                case UAVLINK_MSG_ID_GLOBAL_POSITION:
                    break;
                default:
                    break;
                }
                delete message;
            }
        }


    }
}


