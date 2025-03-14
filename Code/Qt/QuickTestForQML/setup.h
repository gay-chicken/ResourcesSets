#ifndef SETUP_H
#define SETUP_H

#include <QObject>
#include <QQmlEngine>

class Setup : public QObject
{
    Q_OBJECT
public:
    Setup() = default;
    ~Setup() = default;

    void initMain() {
        qDebug("启动测试");
    }

public slots:
    void applicationAvailable();
    void qmlEngineAvailable(QQmlEngine *engine);
    void cleanupTestCase();

private slots:
    void initTestCase() {
        qDebug("初始化测试环境");
    }

    void init() {
        qDebug("进行测试用例初始化工作...");
    }

    void T_print()
    {
        qDebug("测试用例运行中...");
    }

    void cleanup() {
        qDebug("释放测试用例内存...");
    }

    // void cleanupTestCase() {
    //     qDebug("清理测试环境");
    // }
};

#endif // SETUP_H
