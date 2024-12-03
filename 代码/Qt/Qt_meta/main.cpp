#include "Student.h"
#include <QVariant>
#include <QMetaProperty>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Student* stu = new Student("张三", 21);

    const QMetaObject* meta = stu->metaObject();
    qDebug() << "class name: "
             << meta->className();

    int pCount = meta->propertyCount();
    qDebug() << "property count: "
             << pCount;

    for (int i = 0; i < pCount; i++) {
        qDebug() << meta->property(i).typeName() << meta->property(i).name() << stu->property(meta->property(i).name()).toString();
    }

    QMetaObject::invokeMethod(stu, "show");

    return a.exec();
}
