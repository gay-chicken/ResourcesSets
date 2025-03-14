#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QObject>

#include "mythread.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QQmlComponent tree(&engine, QUrl("qrc:/qml/InfoBox.qml"));
    if (tree.isReady()) {
        QQmlContext *root = engine.rootContext();
        QObject *obj = tree.create(root);
        QQuickItem* item = obj->findChild<QQuickItem*>("qml_text");
        if (item == nullptr) qCritical() << "item is nullptr!";
        else {
            qDebug() << item->setProperty("text", "Completed!");
        }
    }

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("ThreadForQML", "Main");

    return app.exec();
}
