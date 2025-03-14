#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QFile>
#include <QQmlContext>

#include "filecontrol.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // qmlRegisterType<FileControl>("MyModule", 1, 0, "FileControl");

    FileControl fileControl;
    engine.rootContext()->setContextProperty("control", &fileControl);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("QTCPP", "Main");

    return app.exec();
}
