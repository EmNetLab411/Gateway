#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab->setAutoFillBackground(true);

    setWindowTitle(tr("GATEWAY IOT"));

    console = new Console(this);
    console->setEnabled(true);
    console->setLocalEchoEnabled(true);
    ui->layoutConsole->addWidget(console);

    ui->labelConnected->setStyleSheet("QLabel { background-color : red; color : black; qproperty-alignment: AlignCenter; font: bold; border-color: rgb(255,255,255); border-width: 2px; border-style: solid; border-radius: 9px; padding: 5px;}");
    ui->labelConnected->setText("MQTT Status: Disconnected");
//    ui->labelSerialPort->setStyleSheet("QLabel { background-color : red; color : black; qproperty-alignment: AlignCenter; font: bold; border-color: rgb(255,255,255); border-width: 2px; border-style: solid; border-radius: 9px; padding: 5px;}");
    ui->label_sub_state->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos_num->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->labe_state->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos_num->setText("0");
    ui->label_sub_state->setText("Unsubscribed");
    ui->labelTcp->setStyleSheet("QLabel { background-color : red; color : black; qproperty-alignment: AlignCenter; font: bold; border-color: rgb(255,255,255); border-width: 2px; border-style: solid; border-radius: 9px; padding: 5px;}");
    ui->labelTcp->setText("UAV connection : Disconnected!");

    config = new settingsfile();

    QPixmap pix(":/resource/icon/Lab_logo.jpg");
    ui->labelLabIcon->setPixmap(pix.scaled(200, 200));

    // video vlc
    _instance = new VlcInstance(VlcCommon::args(), this);
    _instance_below = new VlcInstance(VlcCommon::args(), this);
    _player_forward = new VlcMediaPlayer(_instance);
    _player_below = new VlcMediaPlayer(_instance_below);
    _player_forward->setVideoWidget(ui->video_forward);
    _player_below->setVideoWidget(ui->video_below);
    ui->video_forward->setMediaPlayer(_player_forward);
    ui->video_below->setMediaPlayer(_player_below);
    // rescale to 1:1
    Vlc::Ratio r = Vlc::Ratio::R_1_1;
    ui->video_forward->setDefaultAspectRatio(r);
    ui->video_forward->setAspectRatio(r);
    ui->video_forward->setCurrentCropRatio(r);
    ui->video_forward->setDefaultCropRatio(r);
    ui->video_forward->setCropRatio(r);
    ui->video_forward->enableDefaultSettings();
    ui->video_below->setDefaultAspectRatio(r);
    ui->video_below->setAspectRatio(r);
    ui->video_below->setCurrentCropRatio(r);
    ui->video_below->setDefaultCropRatio(r);
    ui->video_below->setCropRatio(r);
    ui->video_below->enableDefaultSettings();


    createMqttClient();

    connect(this, &MainWindow::signalMqttPublic, mqttClient, &mqttclient::Publish);
    connect(mqttClient->m_client, &QMqttClient::connected, this, &MainWindow::onMqttConntected);
    connect(mqttClient->m_client, &QMqttClient::disconnected, this, &MainWindow::onMqttDisconnect);
    connect(mqttClient->m_client, &QMqttClient::connected, mqttClient, &mqttclient::connectToGateway);
    connect(mqttClient, &mqttclient::signalSubcribe, this, &MainWindow::onSubcribeTopic);

    restClient = new restclient();
    thread_restclient = new QThread();
    restClient->moveToThread(thread_restclient);
    thread_restclient->start();
    udpClient = new udpclient();
    connect(udpClient, &udpclient::new_msg_state_received,mqttClient,&mqttclient::publishDataState);
    connect(udpClient, &udpclient::new_msg_global_position_received,mqttClient,&mqttclient::publishDataGlobalPosition);
    connect(udpClient, &udpclient::new_msg_global_position_received,this, &MainWindow::gps_change_slot);
    connect(udpClient, &udpclient::new_msg_sensor_received,mqttClient,&mqttclient::publishDataSensor);
    connect(restClient, &restclient::new_manual_control_received,udpClient,&udpclient::hold_manual_control_data);
    connect(restClient, &restclient::new_command_received,udpClient,&udpclient::send_msg_command);
    connect(restClient, &restclient::new_control_robot_received,udpClient,&udpclient::send_msg_control_robot);
    connect(restClient, &restclient::new_waypoint_received, udpClient, &udpclient::send_msg_waypoint);
    connect(restClient, &restclient::print_data, console, &Console::printData);
    connect(udpClient, &udpclient::uav_connected, this, &MainWindow::onUavConnected);
}

void MainWindow::testfunct(QNetworkReply *reply)
{
    qDebug()<< reply->readAll();
}
MainWindow::~MainWindow()
{
    mqttClient->disconnectToGateway();
    mqttClient->disconnectToHost();
    delete config;
    delete ui;
}

void MainWindow::gps_change_slot(QByteArray msg)
{
    uavlink_msg_global_position_t global_position;
    global_position.Decode(msg);
    emit gps_change(global_position.getLatitude(), global_position.getLongitude(), global_position.getYaw());
}
void MainWindow::createMqttClient()
{
    mqttClient = new mqttclient(this, config->hostMqtt, config->portMqtt);
    if(mqttClient->m_client->state() == QMqttClient::Disconnected)
    {
        mqttClient->connectToHost();
    }

    onMqttConnecting();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::onMqttConntected()
{
    ui->labelConnected->setStyleSheet("QLabel { background-color : green; "
                                      "color : black; "
                                      "qproperty-alignment: AlignCenter; "
                                      "font: bold;"
                                      "border-color: rgb(255,255,255); "
                                      "border-width: 2px; "
                                      "border-style: solid; "
                                      "border-radius: 9px; "
                                      "padding: 5px;}");
    ui->labelConnected->setText("MQTT Status: Connected");

    console->printData("Connect to Thingsboard MQTT Broker successed!!!");

    mqttClient->Subscribe();
}

void MainWindow::onMqttConnecting()
{
    ui->labelConnected->setStyleSheet("QLabel { background-color : yellow; "
                                      "color : black; "
                                      "qproperty-alignment: AlignCenter; "
                                      "font: bold;"
                                      "border-color: rgb(255,255,255); "
                                      "border-width: 2px; "
                                      "border-style: solid; "
                                      "border-radius: 9px; "
                                      "padding: 5px;}");
    ui->labelConnected->setText("MQTT Status: Connecting!!!");
}

void MainWindow::onMqttDisconnect()
{
    ui->labelConnected->setStyleSheet("QLabel { background-color : red; "
                                      "color : black; "
                                      "qproperty-alignment: AlignCenter; "
                                      "font: bold;"
                                      "border-color: rgb(255,255,255); "
                                      "border-width: 2px; "
                                      "border-style: solid; "
                                      "border-radius: 9px; "
                                      "padding: 5px;}");
    ui->labelConnected->setText("MQTT Status: Disconnected!!!");
    mqttClient->connectToHost();
}

void MainWindow::onSubcribeTopic(bool result)
{
    if(!result)
    {
        console->printData("Error, Could not subscribe. Is there a valid connection?");
        mqttClient->Subscribe();
    }
    else
    {
        console->printData("Subcribe to topic Attributes success!");
        subcribeSuccess = true;
        connect(mqttClient->sub, &mqttsubscription::signalUpdateSubMessage, this, &MainWindow::onMqttSubMessage);
        connect(mqttClient->sub, &mqttsubscription::signalUpdateSubState, this, &MainWindow::onMqttSubUpdateState);
        connect(mqttClient->sub, &mqttsubscription::signalUpdateSubQos, this, &MainWindow::onMqttSubQos);

    }
}

void MainWindow::onMqttSubUpdateState(QString state)
{
    ui->label_sub_state->setText(state);
}

void MainWindow::onMqttSubMessage(QString message)
{
    QVector<QString> type;
    QVector<QVariant> data;
    message.remove(QChar('"'), Qt::CaseInsensitive);
    message.remove(QChar('}'), Qt::CaseInsensitive);
    message.remove(QChar('{'), Qt::CaseInsensitive);
    QStringList msg = message.split(",");
    foreach(QString typeValue, msg)
    {
        QStringList splitData = typeValue.split(":");
        type.append(splitData[0]);
        data.append(splitData[1]);
    }

    QString _message = "\nID: " + data.value(0).toString() + " - Device: " + data.value(1).toString() + " - " + attributes +": " + data.value(2).toString();
    console->printData(_message);


}

void MainWindow::onMqttSubQos(quint8 qos)
{
    ui->label_qos_num->setText(QString::number(qos));
}


void MainWindow::on_disconnectMqttButton_clicked()
{
    mqttClient->disconnectToGateway();
    mqttClient->disconnectToHost();
}


void MainWindow::on_connectMqttButton_clicked()
{
    if(mqttClient->m_client->state() == QMqttClient::Disconnected)
    {
        mqttClient->connectToHost();
    }

    onMqttConnecting();
}


void MainWindow::on_clearButton_clicked()
{
    console->clear();
}


void MainWindow::on_subButton_clicked()
{
    mqttClient->publishAttributesResponse(1, "Sensor1", "attribute1");
    attributes = "attribute1";
}

void MainWindow::on_get_video_forward_clicked()
{
    _media_forward = new VlcMedia("http://192.168.1.100:9000/?action=stream", _instance);
    //reduce latency
    QStringList option_list;
           option_list.append(":network-caching=100");
           option_list.append(":clock-jitter=0");
           option_list.append(":clock-synchro=0");

    _media_forward->setOptions(option_list);
    _player_forward->open(_media_forward);


}


void MainWindow::on_get_video_below_clicked()
{
    _media_below = new VlcMedia("http://192.168.1.100:8080/stream?topic=/main_camera/image_raw", _instance_below);
    //reduce latency
    QStringList option_list;
           option_list.append(":network-caching=100");
           option_list.append(":clock-jitter=0");
           option_list.append(":clock-synchro=0");

    _media_below->setOptions(option_list);
    _player_below->open(_media_below);


}
void MainWindow::onUavConnected()
{
    ui->labelTcp->setStyleSheet("QLabel { background-color : green; color : black; qproperty-alignment: AlignCenter; font: bold; border-color: rgb(255,255,255); border-width: 2px; border-style: solid; border-radius: 9px; padding: 5px;}");
    ui->labelTcp->setText("UAV connection : Connected!");
}

