#include "mqttsubscription.h"

mqttsubscription::mqttsubscription(QMqttSubscription* sub, QObject *parent) : QObject(parent), m_sub(sub)
{
    connect(m_sub, &QMqttSubscription::messageReceived, this, &mqttsubscription::updateMessage);
    connect(m_sub, &QMqttSubscription::stateChanged, this, &mqttsubscription::updateStatus);
    connect(m_sub, &QMqttSubscription::qosChanged, this, &mqttsubscription::updateQos);
}

mqttsubscription::~mqttsubscription()
{
    delete m_sub;
}

void mqttsubscription::updateMessage(const QMqttMessage &msg)
{
    emit signalUpdateSubMessage(msg.payload());
}

void mqttsubscription::updateStatus(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
    case QMqttSubscription::Unsubscribed:
        SubState = "Unsubscribed";
        break;
    case QMqttSubscription::SubscriptionPending:
        SubState = "Pending";
        break;
    case QMqttSubscription::Subscribed:
        SubState = "Subscribed";
        break;
    case QMqttSubscription::Error:
        SubState = "Error";
        break;
    default:
        SubState = "Unknown";
        break;
    }

    emit signalUpdateSubState(SubState);
}

void mqttsubscription::updateQos(quint8 qos)
{
    emit signalUpdateSubQos(qos);
}
