#ifndef STUDENT_H
#define STUDENT_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <iostream>

/*
 * 元对象：
 *      step 1. 直接或间接继承自QObject
 *      step 2. 存在Q_OBJECT宏
 *
 * 反射字段：
 *      通过Q_PROPERTY宏将字段反射字段，并且
 *          way 1: 字段拥有getter/setter访问器
 *          way 2: 为反射字段绑定一个成员变量
 * 反射方法：
 *          way 1: 加 signals, 通过信号触发的方式
 *          way 2: 加 slots
 *          way 3: 加 Q_INVOKABLE
 * 反射类：
 *
 */

class Student : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name) // ①
    Q_PROPERTY(int age MEMBER age) // ②
public:
    Student(QString name, int age) : name(name), age(age) {}
    void setName(const QString &name) {}
    QString getName() const { return "getName"; }

// public slots:
// signals:
    Q_INVOKABLE void show() { qDebug() << "show()"; }
private:
    QString name;
    int age;
};

#endif // STUDENT_H
