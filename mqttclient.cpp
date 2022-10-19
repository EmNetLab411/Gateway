#include "mqttclient.h"

mqttclient::mqttclient(QObject *parent, QString hostName, qint16 port) : QObject(parent)
{
    config = new settingsfile();
    m_client = new QMqttClient(this);
    m_client->setHostname(hostName);
    m_client->setPort(port);
    qDebug()<<hostName<<port;
    m_client->setUsername("c9Q9xAXBosjcysnDy6C3");

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

void mqttclient::publishDataSensor(int sensorID, double lat, double lon, float temp, float hum, float dust)
{
    _topic = config->topic_device_telemetry;
    QString message = "{\"Temperature\":\""+ QString::number(temp) +
            "\" , \"Humidity\":\""+ QString::number(hum) +
            "\", \"Dust Density\":\""+ QString::number(dust) +
            "\" , \"Latitude\":\""+ QString::number(lat, 'f', 8) +
            "\" , \"Longitude\":\""+ QString::number(lon, 'f', 8) + "\"}";
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
}

void mqttclient::publishDataSensorAsGateway(int sensorID, double lat, double lon, float temp, float hum, float dust)
{
    QDateTime current = QDateTime::currentDateTime();
    uint timestame = current.toTime_t();
    publishTypeSensor(sensorID, "Latitude", lat, timestame, 7);
    publishTypeSensor(sensorID, "Longitude", lon, timestame, 7);
    publishTypeSensor(sensorID, "Temperture", temp, timestame, 2);
    publishTypeSensor(sensorID, "Humidity", hum, timestame, 2);
    publishTypeSensor(sensorID, "Dust Density", dust, timestame, 2);

    publishAttributesTypeSensor(sensorID, "Latitude", lat, 7);
    publishAttributesTypeSensor(sensorID, "Longitude", lon, 7);
    publishAttributesTypeSensor(sensorID, "Temperture", temp, 2);
    publishAttributesTypeSensor(sensorID, "Humidity", hum, 2);
    publishAttributesTypeSensor(sensorID, "Dust Density", dust, 2);
}

void mqttclient::publishTypeSensor(int sensorID, QString type, QVariant data, uint timestame, int numberPrefix)
{
    QString payload = "{\"";
    payload += "Sensor ";
    payload += QString::number(sensorID);
    payload += "\": [{\"ts\":";
    payload += QString::number(timestame);payload+="000,\"values\":";
    payload += "{\""+ type+ "\":";
    payload += QString::number(data.toFloat(), 'f', numberPrefix);
    payload += "}}]}";
    QByteArray gatewayTele(payload.toUtf8());
    _topic = config->topic_gateway_telemetry;
    m_client->publish(_topic, gatewayTele);
}

void mqttclient::publishDataState(QByteArray msg)
{
    uavlink_msg_state_t state;
    state.Decode(msg);
    QJsonObject msg_state = {{"Connected",state.getConnected()},{"Armed",state.getArmed()},{"Baterry",state.getBattery()},{"Mode",state.getMode()}};
    QJsonObject msg_mqtt = {{"State",QJsonValue(msg_state)}};
    QJsonDocument msg_mqtt_doc;
    msg_mqtt_doc.setObject(msg_mqtt);
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
    _topic = config->topic_gateway_attribute;
    qDebug()<<msg_mqtt_doc.toJson();
    m_client->publish(_topic, msg_mqtt_doc.toJson());
}

void mqttclient::publishAttributesTypeSensor(int sensorID, QString type, QVariant data, int numberPrefix)
{
    QString payload = "{\"Sensor " + QString::number(sensorID) + "\":{\"";
    payload += type + "\":";
    payload += QString::number(data.toFloat(), 'f', numberPrefix);
    payload += "}}";
    QByteArray gatewayAttrib(payload.toUtf8());
    _topic = config->topic_gateway_attribute;
    m_client->publish(_topic, gatewayAttrib);
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
