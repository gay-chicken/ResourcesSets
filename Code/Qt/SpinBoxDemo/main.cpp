#include "spinboxdemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpinBoxDemo w;
    w.show();
    return a.exec();
}
