#ifndef MQTTSUBSCRIPTION_H
#define MQTTSUBSCRIPTION_H

#include <QObject>
#include <QDebug>
#include <QMqttClient>
#include <QMqttSubscription>

class mqttsubscription : public QObject
{
    Q_OBJECT
public:
    explicit mqttsubscription(QMqttSubscription* sub, QObject *parent = nullptr);
    ~mqttsubscription();

signals:
    void signalUpdateSubState(QString state);
    void signalUpdateSubMessage(QString message);
    void signalUpdateSubQos(quint8 qos);

public slots:
    void updateMessage(const QMqttMessage &msg);
    void updateStatus(QMqttSubscription::SubscriptionState state);
    void updateQos(quint8 qos);

public:
    QMqttSubscription* m_sub;
    QString SubState;
    QString Submessage;
    int qos;

};

#endif // MQTTSUBSCRIPTION_H
