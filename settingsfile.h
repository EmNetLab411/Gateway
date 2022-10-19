#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#define NOFFUNC 3
#define NOSENSOR 5
#define TAKE_TEMP_AND_HUM 0
#define TAKE_PHOTO 1
#define REQUEST_STATUS 2
#define RETASK 3

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QStringList>
#include <map>
#include <iostream>
#include <QDebug>

enum DataType
{
    NO_TYPE,
    TRANSCEIVER_PORT,
    TRANSCEIVER_BAURATE,
    GPS_PORT,
    GPS_BAUDRATE,
    LORA_PORT,
    LORA_BAUDRATE,
    SERIAL_READ_SPEED,
    CONF_THRESOL_FILE_PATH,
    IMAGES_FILE_PATH,
    DATA_FILE_PATH,
    GPS_FILE_PATH,
    HISTORY_FILE_PATH,
    LOG_FILE_PATH,
    TIME_DETECT_FILE_PATH,
    HOST_MQTT,
    PORT_MQTT,
    TOPIC_DEVICE_TELEMETRY,
    TOPIC_GATEWAY_CONNECT,
    TOPIC_GATEWAY_DISCONNECT,
    TOPIC_GATEWAY_ATTRIBUTES,
    TOPIC_GATEWAY_ATTRIBUTES_REQUEST,
    TOPIC_GATEWAY_ATTRUBUTES_RESPONSE,
    TOPIC_GATEWAY_TELEMETRY,
    ACCESS_TOKEN


};

class settingsfile
{

public:
    settingsfile();
    QString SETTINGS_FILE_PATH = "./config.txt";
    QStringList readData;

    QString IMAGES_FILE;
    QString DATA_FILE;
    QString GPS_FILE;
    QString HISTORY_FILE;
    QString LOG_FILE;
    QString TIME_DETECT_FILE;

    QString TRANCEIVER_PORT_DEFAULT;
    int TRANCEIVER_BAUDRATE_DEFAULT;
    QString LORA_PORT_DEFAULT;
    int LORA_BAUDRATE_DEFAULT;
    QString GPS_PORT_DEFAULT;
    int GPS_BAUDRATE_DEFAULT;
    int SERIAL_READ_SPEED_T;
    QString CONF_THRESOL;

    QString hostMqtt;
    int portMqtt;
    QString topic_device_telemetry;
    QString topic_gateway_connect;
    QString topic_gateway_disconnect;
    QString topic_gateway_attribute;
    QString topic_gateway_attribute_request;
    QString topic_gateway_attribute_response;
    QString topic_gateway_telemetry;
    QString ACCESS_TOKEN_H;

    std::map<QString, DataType> s_mapStringValues;

    void readFile(QString dataType, QString data);
    void Initialize();
    void updateConfigSettings();


};

#endif // SETTINGSFILE_H
