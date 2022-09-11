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

    AlwaysOpenSerialPort();
    createMqttClient();

    connect(this, &MainWindow::signalMqttPublic, mqttClient, &mqttclient::Publish);
    connect(mqttClient->m_client, &QMqttClient::connected, this, &MainWindow::onMqttConntected);
    connect(lora, &serialport::signalReceivedData, mqttClient, &mqttclient::publishDataSensor);


}

MainWindow::~MainWindow()
{
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

void MainWindow::on_stopButton_clicked()
{
    mqttClient->testMqtt();
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

