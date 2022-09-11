#ifndef UAVLINK_MSG_SENSOR_T_H
#define UAVLINK_MSG_SENSOR_T_H

#include <QObject>
#include <QDebug>

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
    double _lat;
    double _lon;
    int _id;
    float _temp;
    float _hum;
    float _dust;

};

#endif // UAVLINK_MSG_SENSOR_T_H
