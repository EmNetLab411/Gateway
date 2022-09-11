#ifndef LORA_H
#define LORA_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QStringList>
#include <QTime>

#include "serialport.h"

class lora : public QObject
{
    Q_OBJECT
public:
    explicit lora(QObject *parent = nullptr);

    void open();
signals:

public slots:

public:
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;
};

#endif // LORA_H
