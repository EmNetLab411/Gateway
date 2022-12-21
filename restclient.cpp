#include "restclient.h"

restclient::restclient(QObject *parent) : QObject(parent)
{

    config = new settingsfile();
    get_key_swagger = new QNetworkAccessManager(this);

    key_swagger_request.setUrl(QUrl("https://thingsboard.cloud:443/api/auth/login"));
    key_swagger_request.setRawHeader("accept", "application/json");
    key_swagger_request.setRawHeader("Content-Type", "application/json");

    lastest_command_id = -1;
    manual_control_request_url = "https://thingsboard.cloud:443/api/plugins/telemetry/DEVICE/f27036d0-7441-11ed-8b62-e9eba22b9df6/values/attributes/CLIENT_SCOPE";
    command_request_url = "https://thingsboard.cloud:443/api/plugins/telemetry/DEVICE/2a4fcd90-7442-11ed-b24c-ab40826c689b/values/attributes/CLIENT_SCOPE";
    control_robot_request_url ="https://thingsboard.cloud:443/api/plugins/telemetry/DEVICE/09540c00-7442-11ed-861d-25ac767dd88b/values/attributes/CLIENT_SCOPE";
    msg_waypoint_request_url ="https://thingsboard.cloud:443/api/plugins/telemetry/DEVICE/524635f0-7442-11ed-a3e8-cd953d903e76/values/attributes/CLIENT_SCOPE";

    time_now = new QTime();

    command_receiver = new QNetworkAccessManager(this);
    manual_control_receiver = new QNetworkAccessManager(this);
    control_robot_receiver = new QNetworkAccessManager(this);
    waypoint_receiver = new QNetworkAccessManager(this);

    command_request.setUrl(QUrl(command_request_url));
    manual_control_request.setUrl(QUrl(manual_control_request_url));
    control_robot_request.setUrl(QUrl(control_robot_request_url));
    waypoint_request.setUrl(QUrl(msg_waypoint_request_url));

//    command_request.setRawHeader("X-Authorization",command_key);
//    manual_control_request.setRawHeader("X-Authorization", manual_control_key);
//    control_robot_request.setRawHeader("X-Authorization",control_robot_key);
//    waypoint_request.setRawHeader("X-Authorization",msg_waypoint_key);

    connect(command_receiver, &QNetworkAccessManager::finished, this, &restclient::handle_command);
    connect(manual_control_receiver, &QNetworkAccessManager::finished,this,&restclient::handle_manual_control);
    connect(control_robot_receiver, &QNetworkAccessManager::finished,this,&restclient::handle_control_robot);
    connect(waypoint_receiver, &QNetworkAccessManager::finished,this,&restclient::handle_waypoint);
    connect(get_key_swagger, &QNetworkAccessManager::finished, this, &restclient::handle_new_key);

//    timer_request_key = new QTimer(this);
//    connect(timer_request_key, &QTimer::timeout, this, &restclient::read_key);
//    timer_request_key->start(10000);

   timer_manual_control = new QTimer(this);
   connect(timer_manual_control, &QTimer::timeout,this, &restclient::read_manual_control);
   timer_manual_control->start(200);

    timer_control_robot = new QTimer(this);
    connect(timer_control_robot, &QTimer::timeout,this, &restclient::read_control_robot);
    timer_control_robot->start(200);

    timer_command = new QTimer(this);
    connect(timer_command, &QTimer::timeout,this, &restclient::read_command);
    timer_command->start(1000);

     timer_waypoint = new QTimer(this);
     connect(timer_waypoint, &QTimer::timeout,this, &restclient::read_waypoint);
     timer_waypoint->start(1000);

     QByteArray message_request_key = QString("{\"username\":\"lab411.training@gmail.com\" , \"password\":\"ktttlab411\"}").toUtf8();
     get_key_swagger->post(key_swagger_request,message_request_key);


}



//read message, command using GET method
void restclient::read_key()
{
    QByteArray message_request_key = QString("{\"username\":\"lab411.training@gmail.com\" , \"password\":\"ktttlab411\"}").toUtf8();
    get_key_swagger->post(key_swagger_request,message_request_key);
}
void restclient::read_waypoint()
{
    waypoint_receiver->get(waypoint_request);
}
void restclient::read_command()
{
    command_receiver->get(command_request);
}
void restclient::read_manual_control()
{
    manual_control_receiver->get(manual_control_request);
}
void restclient::read_control_robot()
{
    control_robot_receiver->get(control_robot_request);
}

//read swagger key
void restclient::handle_new_key(QNetworkReply *reply)
{
//    qDebug()<<reply->readAll();
    QJsonDocument _key_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray key_json = _key_json.array();
    QString key_swagger = _key_json.object().value("token").toString();
    manual_control_key = "Bearer "+key_swagger.toUtf8();
    command_key = "Bearer "+key_swagger.toUtf8();
    control_robot_key = "Bearer "+key_swagger.toUtf8();
    msg_waypoint_key = "Bearer "+key_swagger.toUtf8();
    command_request.setRawHeader("X-Authorization",command_key);
    manual_control_request.setRawHeader("X-Authorization", manual_control_key);
    control_robot_request.setRawHeader("X-Authorization",control_robot_key);
    waypoint_request.setRawHeader("X-Authorization",msg_waypoint_key);

}
//handle message, command from GET result
void restclient::handle_manual_control(QNetworkReply *reply)
{
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _manual_control_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray manual_control_json = _manual_control_json.array();
//    qDebug()<<"time manual"<<manual_control_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong();
    if (dt.toMSecsSinceEpoch() - manual_control_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000)
    {
        for(int i=0; i< manual_control_json.count(); i++)
        {
            if (manual_control_json[i].toObject().value("key") == "Vx") Vx = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Vy") Vy = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Vz") Vz = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Yawrate") Yawrate = manual_control_json[i].toObject().value("value").toInt();
        }
        emit new_manual_control_received(Vx,Vy,Vz,Yawrate,true);
        qDebug()<<"rest client: manual control";
    }
    else
    {
        emit new_manual_control_received(Vx,Vy,Vz,Yawrate,false);
        qDebug()<<"rest client: stop manual control";
    }




}

void restclient::handle_command(QNetworkReply *reply)
{
//    qDebug()<<reply->readAll();
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _command_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray command_json = _command_json.array();
    int command_id = command_json[0].toObject().value("value").toInt();
    if (dt.toMSecsSinceEpoch() - command_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000 && (command_id > lastest_command_id || command_id==0))
    {
        qDebug()<<"rest client: new command"<<command_id;
        for(int i=0; i< command_json.count(); i++)
        {
            if (command_json[i].toObject().value("key") == "id") lastest_command_id = command_json[i].toObject().value("value").toInt();
            else if (command_json[i].toObject().value("key") == "param1") param1 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param2") param2 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param3") param3 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param4") param4 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "mode_id") mode_id = command_json[i].toObject().value("value").toInt();

        }
        emit new_command_received(mode_id,param1,param2,param3,param4);
        emit print_data("new command received: ");
    }

}
void restclient::handle_waypoint(QNetworkReply *reply)
{
//    qDebug()<<reply->readAll();
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _waypoint_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray waypoint_json = _waypoint_json.array();
    if (dt.toMSecsSinceEpoch() - waypoint_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000)
    {

        for(int i=0; i< waypoint_json.count(); i++)
        {
            if (waypoint_json[i].toObject().value("key") == "wpid") wpid = waypoint_json[i].toObject().value("value").toInt();
            else if (waypoint_json[i].toObject().value("key") == "altitude") alt = waypoint_json[i].toObject().value("value").toInt();
            else if (waypoint_json[i].toObject().value("key") == "latitude") lat = (float)waypoint_json[i].toObject().value("value").toInt();
            else if (waypoint_json[i].toObject().value("key") == "longitude") lon = waypoint_json[i].toObject().value("value").toInt();
        }
        qDebug()<<"rest client: new waypoint id";
        emit new_waypoint_received(wpid,lat,lon,alt);
    }
}
void restclient::handle_control_robot(QNetworkReply *reply)
{
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _control_robot_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray control_robot_json = _control_robot_json.array();
    if (dt.toMSecsSinceEpoch() - control_robot_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000)
    {
        for(int i=0; i< control_robot_json.count(); i++)
        {
            if (control_robot_json[i].toObject().value("key") == "Step1") Step1 = control_robot_json[i].toObject().value("value").toInt();
            else if (control_robot_json[i].toObject().value("key") == "Step2") Step2 = control_robot_json[i].toObject().value("value").toInt();
            else if (control_robot_json[i].toObject().value("key") == "Step3") Step3 = control_robot_json[i].toObject().value("value").toInt();
            else if (control_robot_json[i].toObject().value("key") == "Step4") Step4 = control_robot_json[i].toObject().value("value").toInt();
            else if (control_robot_json[i].toObject().value("key") == "Step5") Step5 = control_robot_json[i].toObject().value("value").toInt();
        }
        emit new_control_robot_received(Step1,Step2,Step3,Step4,Step5);
    }

}
restclient::~restclient()
{

}
