#include "mainwindow.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QApplication>
//#include "uavlink_msg_global_position_t.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/add_map.qml"));
    //qmlRegisterType<uavlink_msg_global_position_t>("position.marker", 1, 0, "Uavlink_msg_global_position_t");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
   qmlRegisterType<uavlink_msg_global_position_t>("position.marker", 1, 0, "Uavlink_msg_global_position_t");
   engine.load(url);

   return a.exec();

}
