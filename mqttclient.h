#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QDateTime>
#include <QtMqtt/QtMqtt>
#include <QtMqtt/QMqttClient>
#include <QJsonObject>

#include "settingsfile.h"

class mqttclient : public QObject
{
    Q_OBJECT
public:
    explicit mqttclient(QObject *parent = nullptr, QString hostName = "", qint16 port = 0);
    ~mqttclient();

    void connectToHost();
    void disconnectToHost();


signals:

public slots:
    void setClientPort(int p);
    void Publish(QString message);
    void publishDataSensor(int sensorID, double lat, double lon, float temp, float hum, float dust);
    void Subscribe();
    void updateLogStateChange();
    void brokerDisconnected();
    void testMqtt();

public:
    QMqttClient* m_client;

private:
    settingsfile* config;
    QString _topic;

};

#endif // MQTTCLIENT_H
