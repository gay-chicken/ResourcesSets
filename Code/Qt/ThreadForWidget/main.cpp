#include "mainwindow.h"

#include <QApplication>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVector<int>>("QVector<int>");
    MainWindow w;
    w.show();
    return a.exec();
}
