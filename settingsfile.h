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
    CONF_THRESOL_FILE_PATH,
    IMAGES_FILE_PATH,
    DATA_FILE_PATH,
    GPS_FILE_PATH,
    HISTORY_FILE_PATH,
    LOG_FILE_PATH,
    TIME_DETECT_FILE_PATH,
    HOST_MQTT,
    PORT_MQTT,
    TOPIC1,
    TOPIC2,
    ACCESS_TOKEN


};

class settingsfile
{

public:
    settingsfile();
    QString SETTINGS_FILE_PATH = "./WSAN/config.txt";
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
    QString CONF_THRESOL;

    QString hostMqtt;
    int portMqtt;
    QString topic1;
    QString topic2;
    QString ACCESS_TOKEN_H;

    std::map<QString, DataType> s_mapStringValues;

    void readFile(QString dataType, QString data);
    void Initialize();
    void updateConfigSettings();


};

#endif // SETTINGSFILE_H
