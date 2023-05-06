#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPixmap>
#include <QSettings>
#include <QTime>
#include <QLabel>

#include "communication/protocols/messages/messageID.h"
#include "udpclient.h"
#include "settingsfile.h"
#include "console.h"
#include "mqttclient.h"
#include "restclient.h"

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <QNetworkAccessManager>

#include <QtQuick>

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

private:


signals:
    void signalMqttSubcribe();
    void signalMqttPublic(QString message);
    void gps_change(double lat, double lon, int yaw);
public slots:
    void gps_change_slot(QByteArray msg);

private slots:
    void on_pushButton_clicked();
    void onMqttConntected();
    void onMqttConnecting();
    void onMqttDisconnect();
    void onUavConnected();
    void onSubcribeTopic(bool result);
    void onMqttSubUpdateState(QString state);
    void onMqttSubMessage(QString message);
    void onMqttSubQos(quint8 qos);
    void testfunct(QNetworkReply *reply);
    void on_disconnectMqttButton_clicked();

    void on_connectMqttButton_clicked();

    void on_clearButton_clicked();

    void on_subButton_clicked();

    void on_get_video_forward_clicked();

    void on_get_video_below_clicked();

    void hold_manual_control_data(qint32 Vx, qint32 Vy, qint32 Vz, qint32 Yawrate, bool is_new);
    void send_msg_command(qint16 mode_id, float param1, float param2, float param3, float param4);
    void send_msg_control_robot(qint32 Step1, qint32 Step2, qint32 Step3, qint32 Step4, qint32 Step5);
    void send_msg_waypoint(qint32 waypointId, qint32 lat, qint32 lon, qint32 alt);


public:
    settingsfile* config;
private:
    Ui::MainWindow *ui;
    Console* console;
    restclient* restClient;
    udpclient* udpClient;
    QThread* thread_restclient;
    QString _organizationName, _appname;
    bool transceiverStarted, sended, detectedFlag, loraStarted, subcribeSuccess = false;
    mqttclient* mqttClient;
    QString attributes;
    //vlc video
    VlcInstance *_instance,*_instance_below;
    VlcMedia *_media_forward, *_media_below;
    VlcMediaPlayer *_player_forward, *_player_below;
};
#endif // MAINWINDOW_H
