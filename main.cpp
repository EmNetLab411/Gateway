#include "mainwindow.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QApplication>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/add_map.qml"));

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("Mainwindow", &w);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

   engine.load(url);

   return a.exec();

}
