#include <QElapsedTimer>
#include <QDebug>

#include "mythread.h"

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{}

void MyThread::run()
{
    qDebug() << "Thread Address: " << QThread::currentThread();
    QVector<int> vec;
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < this->num_; i++) {
        vec.push_back(rand() % 117321);
    }
    int millsec = timer.elapsed();
    qDebug() << "pass time: " << millsec << "ms";
    emit sendArray(vec);
}

void MyThread::recvNum(int num)
{
    this->num_ = num;
}
