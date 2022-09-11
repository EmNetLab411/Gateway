#ifndef UAVLINK_MSG_SENSOR_T_H
#define UAVLINK_MSG_SENSOR_T_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <QDataStream>

class uavlink_msg_sensor_t : public QObject
{
    Q_OBJECT
public:
    explicit uavlink_msg_sensor_t(QObject *parent = nullptr);
    int getSensorID();
    float getTemp();
    float getHum();
    float getDust();
    double getLat();
    double getLon();
    QByteArray getData();
    void Decode(QByteArray data);

signals:

private:
    qint32 _lat;
    qint32 _lon;
    qint16 _id;
    qint16 _temp;
    qint16 _hum;
    qint16 _dust;

};

#endif // UAVLINK_MSG_SENSOR_T_H
