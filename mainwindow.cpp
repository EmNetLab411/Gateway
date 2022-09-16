#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui->labelSerialPort->setStyleSheet("QLabel { background-color : red; color : black; qproperty-alignment: AlignCenter; font: bold; border-color: rgb(255,255,255); border-width: 2px; border-style: solid; border-radius: 9px; padding: 5px;}");
    ui->label_sub_state->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos_num->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->labe_state->setStyleSheet("QLabel { background-color : white; color : black; qproperty-alignment: AlignCenter; font: nomal; border-color: rgb(255,255,255); padding: 5px;}");
    ui->label_qos_num->setText("0");
    ui->label_sub_state->setText("Unsubscribed");

    config = new settingsfile();

    QPixmap pix(":/resource/icon/Lab_logo.jpg");
    ui->labelLabIcon->setPixmap(pix.scaled(200, 200));

    lora = new serialport();
    loraStarted = false;
    thread_lora = new QThread();
    lora->moveToThread(thread_lora);

    connect(lora, &serialport::signalOpenSerialPort, thread_lora, &QThread::start);
    connect(thread_lora, &QThread::started, lora, &serialport::openSerialPort);
    connect(lora, &serialport::signalReceivedData, this, &MainWindow::onPrintSensorData);
    connect(lora->timer, &QTimer::timeout, this, &MainWindow::checkSerialPort);

    checkSerialPort();
    createMqttClient();

    connect(this, &MainWindow::signalMqttPublic, mqttClient, &mqttclient::Publish);
    connect(mqttClient->m_client, &QMqttClient::connected, this, &MainWindow::onMqttConntected);
    connect(mqttClient->m_client, &QMqttClient::disconnected, this, &MainWindow::onMqttDisconnect);
    connect(mqttClient->m_client, &QMqttClient::connected, mqttClient, &mqttclient::connectToGateway);
    //connect(lora, &serconfig->updateConfigSettings();ialport::signalReceivedData, mqttClient, &mqttclient::publishDataSensor);
    connect(lora, &serialport::signalReceivedData, mqttClient, &mqttclient::publishDataSensorAsGateway);
    connect(mqttClient, &mqttclient::signalSubcribe, this, &MainWindow::onSubcribeTopic);
}

MainWindow::~MainWindow()
{
    mqttClient->disconnectToGateway();
    mqttClient->disconnectToHost();
    delete config;
    delete thread_lora;
    delete lora;
    delete ui;
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

void MainWindow::AlwaysOpenSerialPort()
{
    settingsfile config;
    if(loraStarted)
    {
        if(lora->port->isOpen())
        {
            lora->port->close();
            console->insertPlainText("\n-------------- Lora Closed -------------\n");
        }
        else
        {
            if(lora->port->portName().isEmpty())
            {
                lora->port->setPortName(config.LORA_PORT_DEFAULT);
            }
            QSettings settings(_organizationName, _appname);
            QString tmp = settings.value("TranceiverBaudrate").toString();
            if(tmp.isEmpty())
            {
                lora->port->setBaudRate((BaudRateType) config.LORA_BAUDRATE_DEFAULT);
            }
            lora->port->open(QIODevice::ReadWrite);
            console->insertPlainText("\n------------- Port Lora Data Opened ------------\n");
        }
    }
    else
    {
        lora->requestOpenSerialPort();
        console->insertPlainText("\n-------------- Port Lora Data Opened -------------\n");
        loraStarted = true;
    }
}

void MainWindow::onPrintSensorData(int idSensor, double lat, double lon, float temp, float hum, float dust)
{

    QString tmp = "\n[" + QTime::currentTime().toString() + "]" + " Collect data from sensor: "+ QString::number(idSensor) +"\r\n";
    tmp += "Latitude: ";
    tmp += QString::number(lat, 'f', 10);
    tmp += "    ||    Longitude: ";
    tmp += QString::number(lon, 'f', 10);
    tmp += "\nTemperature: ";
    tmp += QString::number(temp);
    tmp += " oC    ||    Humidity: ";
    tmp += QString::number(hum);
    tmp += " %    ||    Dust: ";
    tmp += QString::number(dust);
    tmp += " %\n";



    console->printData(tmp);


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

void MainWindow::checkSerialPort()
{
    if(!lora->port->isOpen())
    {
        ui->labelSerialPort->setStyleSheet("QLabel { background-color : red; "
                                          "color : black; "
                                          "qproperty-alignment: AlignCenter; "
                                          "font: bold;"
                                          "border-color: rgb(255,255,255); "
                                          "border-width: 2px; "
                                          "border-style: solid; "
                                          "border-radius: 9px; "
                                          "padding: 5px;}");
        ui->labelSerialPort->setText("Serial Port: Closed!!!");

        lora->requestOpenSerialPort();
        console->insertPlainText("\n-------------- Port Lora Data Opened -------------\n");
    }
    else
    {
        ui->labelSerialPort->setStyleSheet("QLabel { background-color : green; "
                                          "color : black; "
                                          "qproperty-alignment: AlignCenter; "
                                          "font: bold;"
                                          "border-color: rgb(255,255,255); "
                                          "border-width: 2px; "
                                          "border-style: solid; "
                                          "border-radius: 9px; "
                                          "padding: 5px;}");
        ui->labelSerialPort->setText("Serial Port: Opened!!!");
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
    console->printData(message);
    QStringList msg = message.split(",");
    foreach(QString typeValue, msg)
    {
        QStringList splitData = typeValue.split(":");
        type.append(splitData[0]);
        data.append(splitData[1]);
    }

    QString _message = "ID: " + data.value(0).toString() + " - Device: " + data.value(1).toString() + " - " + attributes +": " + data.value(2).toString();
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
    mqttClient->publishAttributesResponse(1, "Sensor 1", "Latitude");
    attributes = "Latitude";
}

