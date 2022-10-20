#include "restclient.h"

restclient::restclient(QObject *parent) : QObject(parent)
{
    lastest_command_id = -1;
    manual_control_request_url = "https://demo.thingsboard.io:443/api/plugins/telemetry/DEVICE/f3d0e1f0-4e26-11ed-b827-c9be76c6f5d7/values/attributes/CLIENT_SCOPE";
    manual_control_key = "Bearer eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJ0cmFpbmluZy5sYWI0MTFAZ21haWwuY29tIiwidXNlcklkIjoiN2FhZTNmMTAtMjE5Yi0xMWVjLWI0YTUtY2ZiMjg5YWYzOGQ5Iiwic2NvcGVzIjpbIlRFTkFOVF9BRE1JTiJdLCJpc3MiOiJ0aGluZ3Nib2FyZC5pbyIsImlhdCI6MTY2NjAxNTgxMywiZXhwIjoxNjY3ODE1ODEzLCJmaXJzdE5hbWUiOiI0MTEiLCJsYXN0TmFtZSI6ImxhYiIsImVuYWJsZWQiOnRydWUsInByaXZhY3lQb2xpY3lBY2NlcHRlZCI6dHJ1ZSwiaXNQdWJsaWMiOmZhbHNlLCJ0ZW5hbnRJZCI6IjdhMjU2MDAwLTIxOWItMTFlYy1iNGE1LWNmYjI4OWFmMzhkOSIsImN1c3RvbWVySWQiOiIxMzgxNDAwMC0xZGQyLTExYjItODA4MC04MDgwODA4MDgwODAifQ.-dujRMl93EHxyui4tcJPw9Fl17G6bgqzGDJ_usTUHuW2Lp-faWpz-L0QwlslzSPjT8VfF_k3AugIPCJ4PS4cQg";
    command_request_url = "https://demo.thingsboard.io:443/api/plugins/telemetry/DEVICE/fcf6f440-4e26-11ed-b827-c9be76c6f5d7/values/attributes/CLIENT_SCOPE";
    command_key = "Bearer eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJ0cmFpbmluZy5sYWI0MTFAZ21haWwuY29tIiwidXNlcklkIjoiN2FhZTNmMTAtMjE5Yi0xMWVjLWI0YTUtY2ZiMjg5YWYzOGQ5Iiwic2NvcGVzIjpbIlRFTkFOVF9BRE1JTiJdLCJpc3MiOiJ0aGluZ3Nib2FyZC5pbyIsImlhdCI6MTY2NjAxNTgxMywiZXhwIjoxNjY3ODE1ODEzLCJmaXJzdE5hbWUiOiI0MTEiLCJsYXN0TmFtZSI6ImxhYiIsImVuYWJsZWQiOnRydWUsInByaXZhY3lQb2xpY3lBY2NlcHRlZCI6dHJ1ZSwiaXNQdWJsaWMiOmZhbHNlLCJ0ZW5hbnRJZCI6IjdhMjU2MDAwLTIxOWItMTFlYy1iNGE1LWNmYjI4OWFmMzhkOSIsImN1c3RvbWVySWQiOiIxMzgxNDAwMC0xZGQyLTExYjItODA4MC04MDgwODA4MDgwODAifQ.-dujRMl93EHxyui4tcJPw9Fl17G6bgqzGDJ_usTUHuW2Lp-faWpz-L0QwlslzSPjT8VfF_k3AugIPCJ4PS4cQg";
    control_robot_request_url ="https://demo.thingsboard.io:443/api/plugins/telemetry/DEVICE/a9d6c750-4fba-11ed-a339-0708081d40ce/values/attributes/CLIENT_SCOPE";
    control_robot_key = "Bearer eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJ0cmFpbmluZy5sYWI0MTFAZ21haWwuY29tIiwidXNlcklkIjoiN2FhZTNmMTAtMjE5Yi0xMWVjLWI0YTUtY2ZiMjg5YWYzOGQ5Iiwic2NvcGVzIjpbIlRFTkFOVF9BRE1JTiJdLCJpc3MiOiJ0aGluZ3Nib2FyZC5pbyIsImlhdCI6MTY2NjE1MDY2OCwiZXhwIjoxNjY3OTUwNjY4LCJmaXJzdE5hbWUiOiI0MTEiLCJsYXN0TmFtZSI6ImxhYiIsImVuYWJsZWQiOnRydWUsInByaXZhY3lQb2xpY3lBY2NlcHRlZCI6dHJ1ZSwiaXNQdWJsaWMiOmZhbHNlLCJ0ZW5hbnRJZCI6IjdhMjU2MDAwLTIxOWItMTFlYy1iNGE1LWNmYjI4OWFmMzhkOSIsImN1c3RvbWVySWQiOiIxMzgxNDAwMC0xZGQyLTExYjItODA4MC04MDgwODA4MDgwODAifQ.aVDqJ4D5oGrUVd15jBrotdO1dXfH3Z5EMwVx4EDn79lMAFQJ_DTXLABLuGrC5rOifya7o6vVTzV_YNdC06HYAQ";
    time_now = new QTime();

    command_receiver = new QNetworkAccessManager(this);
    manual_control_receiver = new QNetworkAccessManager(this);
    control_robot_receiver = new QNetworkAccessManager(this);

    command_request.setUrl(QUrl(command_request_url));
    manual_control_request.setUrl(QUrl(manual_control_request_url));
    control_robot_request.setUrl(QUrl(control_robot_request_url));


    command_request.setRawHeader("X-Authorization",command_key);

    manual_control_request.setRawHeader("X-Authorization", manual_control_key);

    control_robot_request.setRawHeader("X-Authorization",control_robot_key);

    connect(command_receiver, &QNetworkAccessManager::finished, this, &restclient::handle_command);
    connect(manual_control_receiver, &QNetworkAccessManager::finished,this,&restclient::handle_manual_control);
    connect(control_robot_receiver, &QNetworkAccessManager::finished,this,&restclient::handle_control_robot);

    timer_manual_control = new QTimer(this);
    connect(timer_manual_control, &QTimer::timeout,this, &restclient::read_manual_control);
    timer_manual_control->start(500);

    timer_control_robot = new QTimer(this);
    connect(timer_control_robot, &QTimer::timeout,this, &restclient::read_control_robot);
    timer_control_robot->start(1000);

//    timer_command = new QTimer(this);
//    connect(timer_command, &QTimer::timeout,this, &restclient::read_command);
//    timer_command->start(2000);

}



//read message, command using GET method
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
//handle message, command from GET result
void restclient::handle_manual_control(QNetworkReply *reply)
{
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _manual_control_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray manual_control_json = _manual_control_json.array();
//    qDebug()<<manual_control_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong();
    // check timeout < 1s
    if (dt.toMSecsSinceEpoch() - manual_control_json[1].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000)
    {
        for(int i=0; i< manual_control_json.count(); i++)
        {
            if (manual_control_json[i].toObject().value("key") == "Vx") Vx = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Vy") Vy = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Vz") Vz = manual_control_json[i].toObject().value("value").toInt();
            else if (manual_control_json[i].toObject().value("key") == "Yawrate") Yawrate = manual_control_json[i].toObject().value("value").toInt();
        }
        emit new_manual_control_received(Vx,Vy,Vz,Yawrate,true);
    }
    else emit new_manual_control_received(Vx,Vy,Vz,Yawrate,false);
}

void restclient::handle_command(QNetworkReply *reply)
{
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _command_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray command_json = _command_json.array();

    int command_id = command_json[0].toObject().value("value").toInt();
    if (dt.toMSecsSinceEpoch() - command_json[1].toObject().value("lastUpdateTs").toVariant().toLongLong() < 1000 && (command_id > lastest_command_id || command_id==0))
    {
    // check time delay < 1s
        for(int i=0; i< command_json.count(); i++)
        {
            if (command_json[i].toObject().value("key") == "id") lastest_command_id = command_json[i].toObject().value("value").toInt();
            else if (command_json[i].toObject().value("key") == "param1") param1 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param2") param2 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param3") param3 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "param4") param4 = command_json[i].toObject().value("value").toDouble();
            else if (command_json[i].toObject().value("key") == "mode_id") mode_id = command_json[i].toObject().value("value").toInt();

        }
//        uavlink_msg_command_t test(mode_id,param1,param2,param3,param4);
//        qDebug()<<test.ToPackage();
        emit new_command_received(mode_id,param1,param2,param3,param4);
    }

}
void restclient::handle_waypoint(QNetworkReply *reply)
{
    qDebug()<< reply->readAll();
}
void restclient::handle_control_robot(QNetworkReply *reply)
{
    QDateTime dt = QDateTime :: currentDateTime();
    QJsonDocument _control_robot_json = QJsonDocument::fromJson(reply->readAll());
    QJsonArray control_robot_json = _control_robot_json.array();
    qDebug()<<control_robot_json[0].toObject().value("lastUpdateTs").toVariant().toLongLong();
    // check timeout < 1s
    if (dt.toMSecsSinceEpoch() - control_robot_json[1].toObject().value("lastUpdateTs").toVariant().toLongLong() < 3000)
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
