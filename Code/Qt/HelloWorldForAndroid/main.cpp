#include "helloworld.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Helloworld w;
    w.show();
    return a.exec();
}
