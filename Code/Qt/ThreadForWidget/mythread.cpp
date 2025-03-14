#include <QElapsedTimer>
#include <QDebug>
#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject{parent} {}

// MyThread::MyThread(QObject *parent) : QThread{parent} {}

void MyThread::working(int num)
{
    qDebug() << "MyThread Address: " << QThread::currentThread();
    QVector<int> vec;
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < num; i++) {
        vec.push_back(rand() % 10000);
    }
    int millsec = timer.elapsed();
    qDebug() << "pass time: " << millsec << "ms";
    emit sendArray(vec);
}

// void MyThread::run()
// {
//     qDebug() << "MyThread Address: " << QThread::currentThread();
//     QVector<int> vec;
//     QElapsedTimer timer;
//     timer.start();
//     for (int i = 0; i < this->num_; i++) {
//         vec.push_back(rand() % 10000);
//     }
//     int millsec = timer.elapsed();
//     qDebug() << "pass time: " << millsec << "ms";
//     emit sendArray(vec);
// }

// void MyThread::recvNum(int num)
// {
//     this->num_ = num;
// }



BubbleSort::BubbleSort(QObject *parent) : QObject(parent) {}

// BubbleSort::BubbleSort(QObject *parent) : QThread(parent) {}

void BubbleSort::working(QVector<int> vec)
{
    qDebug() << "BubbleSort Address: " << QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = 0; j < vec.size() - 1 - i; j++) {
            if (vec[j] > vec[j+1]) {
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
    int millsec = timer.elapsed();
    qDebug() << "pass time: " << millsec << "ms";
    emit finish(vec);
}

// void BubbleSort::run()
// {
//     qDebug() << "BubbleSort Address: " << QThread::currentThread();
//     QElapsedTimer timer;
//     timer.start();
//     for (int i = 0; i < this->vec_.size() - 1; i++) {
//         for (int j = 0; j < this->vec_.size() - 1 - i; j++) {
//             if (this->vec_[j] > this->vec_[j+1]) {
//                 int temp = this->vec_[j];
//                 this->vec_[j] = this->vec_[j+1];
//                 this->vec_[j+1] = temp;
//             }
//         }
//     }
//     int millsec = timer.elapsed();
//     qDebug() << "pass time: " << millsec << "ms";
//     emit finish(this->vec_);
// }

// void BubbleSort::recvVec(QVector<int> vec)
// {
//     this->vec_ = vec;
// }

QuickSort::QuickSort(QObject *parent) : QObject(parent) {}

void QuickSort::working(QVector<int> vec)
{
    qDebug() << "QuickSort Address: " << QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    std::sort(vec.begin(), vec.end(), [](int x, int y){
        return x < y;
    });
    int millsec = timer.elapsed();
    qDebug() << "pass time: " << millsec << "ms";
    emit finish(vec);
}

// QuickSort::QuickSort(QObject *parent) : QThread(parent) {}

// void QuickSort::run()
// {
//     qDebug() << "QuickSort Address: " << QThread::currentThread();
//     QElapsedTimer timer;
//     timer.start();
//     std::sort(this->vec_.begin(), this->vec_.end(), [](int x, int y){
//         return x < y;
//     });
//     int millsec = timer.elapsed();
//     qDebug() << "pass time: " << millsec << "ms";
//     emit finish(this->vec_);
// }

// void QuickSort::recvVec(QVector<int> vec)
// {
//     this->vec_ = vec;
// }
