#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QDateTime>
#include <QtMqtt/QtMqtt>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>
#include <QJsonObject>

#include "settingsfile.h"
#include "mqttsubscription.h"
#include "communication/protocols/messages/uavlink_msg_state_t.h"
#include "communication/protocols/messages/uavlink_msg_global_position_t.h"
#include "communication/protocols/messages/uavlink_msg_sensor_t.h"

class mqttclient : public QObject
{
    Q_OBJECT
public:
    explicit mqttclient(QObject *parent = nullptr, QString hostName = "", qint16 port = 0);
    ~mqttclient();

    void connectToHost();
    void disconnectToHost();
    void disconnectToGateway();
    void publishAttributesResponse(int requestId, QString device, QString value);

signals:
    void signalSubcribe(bool result);

public slots:
    void setClientPort(int p);
    void Publish(QString message);
    void publishDataSensor(QByteArray msg);
    void publishDataState(QByteArray msg);
    void publishDataGlobalPosition(QByteArray msg);
    void Subscribe();
    void updateLogStateChange();
    void brokerDisconnected();
    void testMqtt();
    void connectToGateway();
    void onSubMessage(const QMqttMessage &msg);

public:
    QMqttClient* m_client;
    QMqttSubscription* m_sub;
    mqttsubscription* sub;


private:
    settingsfile* config;
    QString _topic;

};

#endif // MQTTCLIENT_H
