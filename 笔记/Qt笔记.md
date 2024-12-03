# QT笔记

## 信号与槽

| 连接方式           | 描述 | 示例 |
| ------------------ | ---- | ---- |
| QObject::connect   |      |      |
| C++11 Lambda表达式 |      |      |
| 函数指针           |      |      |
| 自动连接           |      |      |



```c++
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 2. 在构造函数中绑定
    QObject::connect(ui->btnSignal_2, SIGNAL(clicked()), this, SLOT(myslotfor2()));

    // 3. 使用C++11 Lambda表达式
    QObject::connect(ui->btnSignal_3, &QPushButton::clicked, [=](){
        std::cout << "Signal 3" << std::endl;
    });

    // 4. 自动连接
    QObject::connect(ui->btnSignal_4, &QPushButton::clicked, this, &MainWindow::myslotfor4);

    // 连接自定义信号与槽，使用emit触发信号
    QObject::connect(this, SIGNAL(mysignal(int)), this, SLOT(myslot(int)));
    emit mysignal(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 1. on_<Object name>_<Signal name>()
void MainWindow::on_btnSignal_1_clicked()
{
    std::cout << "Signal 1"<< std::endl;
}

// 2. 在构造函数中绑定
void MainWindow::myslotfor2()
{
    std::cout << "Signal 2" << std::endl;
}

// 4. 自动连接
void MainWindow::myslotfor4()
{
    std::cout << "Signal 4" << std::endl;
}

// 自定义槽实现
void MainWindow::myslot(int x)
{
    std::cout << "x: "  << x << std::endl;
}

```



## 元对象

```c++
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
```

```C++
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
```



## 文件IO

QFile

文件读写、创建删除

| 名称                           | 功能               | 示例                                             |
| ------------------------------ | ------------------ | ------------------------------------------------ |
| QFile(const QString &filename) | 创建一个文件流对象 | QFile file("test.txt")                           |
| open(OpenMode mode)            | 打开文件流对象     | file.open(QIODevice::ReadOnly \|QIODevice::Text) |
| read                           |                    |                                                  |
| write                          |                    |                                                  |



## 快捷键

QShortcut



## 文件选择弹窗

QFileDialog



## 文件读写

QFile



## 字符流读写

QTextStream





