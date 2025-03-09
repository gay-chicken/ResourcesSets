#include "qtimerdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimerDemo w;
    w.show();
    return a.exec();
}
