#include "datetimedemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateTimeDemo w;
    w.show();
    return a.exec();
}
