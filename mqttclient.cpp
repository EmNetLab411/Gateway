#include "mqttclient.h"

mqttclient::mqttclient(QObject *parent, QString hostName, qint16 port) : QObject(parent)
{
    config = new settingsfile();
    m_client = new QMqttClient(this);
    m_client->setHostname(hostName);
    m_client->setPort(port);
    m_client->setUsername(config->ACCESS_TOKEN_H);
    _topic = config->topic1;

    connect(m_client, &QMqttClient::stateChanged, this, &mqttclient::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &mqttclient::brokerDisconnected);

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
        m_client->disconnectFromHost();
    }
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
    QString message = "{\"Temperature\":\""+ QString::number(temp) +
            "\" , \"Humidity\":\""+ QString::number(hum) +
            "\", \"Dust Density\":\""+ QString::number(dust) +
            "\" , \"Latitude\":\""+ QString::number(lat, 'f', 8) +
            "\" , \"Longitude\":\""+ QString::number(hum, 'f', 8) + "\"}";
    QByteArray publicMessage = message.toUtf8();
    m_client->publish(_topic, publicMessage);
}

void mqttclient::Subscribe()
{
    auto subscroption = m_client->subscribe(_topic);
    if(!subscroption)
    {

    }
}
