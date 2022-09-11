#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPixmap>
#include <QSettings>
#include <QTime>
#include <QLabel>

#include "communication/protocols/messages/messageID.h"
#include "settingsfile.h"
#include "console.h"
#include "serialport.h"
#include "mqttclient.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMqttClient();
    void AlwaysOpenSerialPort();

private:


signals:
    void signalMqttSubcribe();
    void signalMqttPublic(QString message);

private slots:
    void onPrintSensorData(int idSensor, double lat, double lon, float temp, float hum, float dust);
    void on_pushButton_clicked();
    void on_stopButton_clicked();
    void onMqttConntected();
    void onMqttConnecting();

public:
    settingsfile* config;
private:
    Ui::MainWindow *ui;
    Console* console;
    QThread* thread_lora;
    QString _organizationName, _appname;
    bool transceiverStarted, sended, detectedFlag, loraStarted;
    serialport* lora;
    mqttclient* mqttClient;
};
#endif // MAINWINDOW_H
