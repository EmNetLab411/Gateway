#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QList>
#include <QThread>
#include <QJsonObject>

#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "settingsfile.h"
#include "communication/protocols/uavlink_message_t.h"
#include "communication/protocols/messages/messageID.h"
#include "communication/protocols/messages/uavlink_msg_sensor_t.h"


class serialport : public QObject
{
    Q_OBJECT
public:
    explicit serialport(QObject *parent = nullptr);
    ~serialport();
    void requestOpenSerialPort();
    void writeData(QByteArray sendData);

signals:
    void signalOpenSerialPort(QThread::Priority);
    void signalReceivedData(int idSensor, float lat, float lon, float temp, float hum, float dust);

public slots:
    void readData();
    void openSerialPort();

public:
    QextSerialPort* port;
    QTimer* timer;
    QextSerialEnumerator *enumerator;
    settingsfile configFile;

private:
    QByteArray* buffer;

};

#endif // SERIALPORT_H
