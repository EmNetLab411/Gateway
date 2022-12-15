#include "mqttclient.h"

mqttclient::mqttclient(QObject *parent, QString hostName, qint16 port) : QObject(parent)
{
    config = new settingsfile();
    m_client = new QMqttClient(this);
    m_client->setHostname(hostName);
    m_client->setPort(port);
    qDebug()<<hostName<<port;
    m_client->setUsername("BqhCLP5b9pJqmP2mjo5z");


    connect(m_client, &QMqttClient::stateChanged, this, &mqttclient::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &mqttclient::brokerDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
            const QString content = QDateTime::currentDateTime().toString()
                        + QLatin1String(" Received Topic: ")
                        + topic.name()
                        + QLatin1String(" Message: ")
                        + message
                        + QLatin1Char('\n');
            qDebug()<<content;
        });
}

mqttclient::~mqttclient()
{
    delete config;
}

void mqttclient::connectToHost()
{
    if(m_client->state() == QMqttClient::Disconnected)
    {
        m_client->connectToHost();

    }
}

void mqttclient::disconnectToHost()
{
    if(m_client->state() == QMqttClient::Connected)
    {
        qDebug()<<"why";
        m_client->disconnectFromHost();
    }
}

void mqttclient::connectToGateway()
{
    _topic = config->topic_gateway_connect;
    QString message = "{\"device\":\"Gateway\"}";
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
}

void mqttclient::onSubMessage(const QMqttMessage &msg)
{
    qDebug() << msg.payload();
}

void mqttclient::disconnectToGateway()
{
    _topic = config->topic_gateway_disconnect;
    QString message = "{\"device\":\"Gateway\"}";
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
}

void mqttclient::setClientPort(int p)
{
    m_client->setPort(p);
}

void mqttclient::updateLogStateChange()
{

}

void mqttclient::brokerDisconnected()
{

    if(m_client->state() == QMqttClient::Connected)
    {
        qDebug()<<"why";
        m_client->disconnectFromHost();
    }
}

void mqttclient::testMqtt()
{
    QString message = "{\"decive\":\"10\" , \"Gateway\":\"20\"}";
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
}

void mqttclient::Publish(QString message)
{
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
    if (m_client->publish(_topic, publicMessage) == -1)
    {

    }

}

void mqttclient::publishDataSensor(QByteArray msg)
{
   uavlink_msg_sensor_t sensor;
   sensor.Decode(msg);
   QJsonObject msg_sensor = {{"SensorID",sensor.getSensorID()}, {"Latitude",sensor.getLat()}, {"Longitude",sensor.getLon()},
                            {"Temperature",sensor.getTemp()}, {"Huminity",sensor.getHum()}, {"Gas",sensor.getGas()}, {"TDS",sensor.getTDS()}, {"pH",sensor.getPH()}};
   QJsonObject msg_mqtt = {{"Sensor", QJsonValue(msg_sensor)}};
   QJsonDocument msg_mqtt_doc;
   msg_mqtt_doc.setObject(msg_mqtt);
   _topic = config->topic_gateway_attribute;
   m_client->publish(_topic, msg_mqtt_doc.toJson());
}

void mqttclient::publishDataState(QByteArray msg)
{
    uavlink_msg_state_t state;
    state.Decode(msg);
    QJsonObject msg_state = {{"Connected",state.getConnected()},{"Armed",state.getArmed()},{"Baterry",state.getBattery()},{"Mode",state.getMode()}};
    QJsonObject msg_mqtt = {{"State",QJsonValue(msg_state)}};
    QJsonDocument msg_mqtt_doc;
    msg_mqtt_doc.setObject(msg_mqtt);
//    qDebug()<<"mqtt client"<<msg_mqtt;
    _topic = config->topic_gateway_attribute;
    m_client->publish(_topic, msg_mqtt_doc.toJson());
}

void mqttclient::publishDataGlobalPosition(QByteArray msg)
{
    uavlink_msg_global_position_t global_position;
    global_position.Decode(msg);
    QJsonObject msg_global_position = {{"Latitude",global_position.getLatitude()},{"Longitude",global_position.getLongitude()},{"Altitude",global_position.getAltitude()},
                                       {"Vx",global_position.getVx()},{"Vy",global_position.getVy()},{"Vz",global_position.getVz()},{"Yaw",global_position.getYaw()}};
    QJsonObject msg_mqtt = {{"Global Position",QJsonValue(msg_global_position)}};
    QJsonDocument msg_mqtt_doc;
    msg_mqtt_doc.setObject(msg_mqtt);
//    qDebug()<<"mqtt client"<<msg_mqtt;
    _topic = config->topic_gateway_attribute;
    m_client->publish(_topic, msg_mqtt_doc.toJson());
}

void mqttclient::publishAttributesResponse(int requestId, QString device, QString value)
{
    QString payload = "{\"id\":" + QString::number(requestId) + ",";
    payload += "\"device\":\"" + device + "\",";
    payload += "\"client\": true,";
    payload += "\"key\":\"" + value + "\"}";
    QByteArray subAttrib(payload.toUtf8());
    _topic = config->topic_gateway_attribute_request;
    m_client->publish(_topic, subAttrib);
}

void mqttclient::Subscribe()
{
    _topic = config->topic_gateway_attribute;
    auto subcribtion = m_client->subscribe(_topic);
    if(!subcribtion)
    {

        emit signalSubcribe(false);
    } else
    {

        sub = new mqttsubscription(subcribtion, this);
        emit signalSubcribe(true);
    }
}
