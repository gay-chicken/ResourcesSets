#include <QGuiApplication>
#include <QtQml>
#include <QTime>

class CurrentTime {
public:
    QString value() { return QTime::currentTime().toString(); }
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []() { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);

    CurrentTime current;
    engine.rootContext()->setContextProperty("current", current.value());
    engine.loadFromModule("ExtensionForQML", "Main");

    return app.exec();
}
