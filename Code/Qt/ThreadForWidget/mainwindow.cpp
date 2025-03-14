#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Addition
    QThread *t1 = new QThread(this);    // 释放方式1：指定父对象，在父对象析构时会自动析构子对象
    QThread *t2 = new QThread;
    QThread *t3 = new QThread;

    MyThread *my_t = new MyThread;
    BubbleSort *bubble = new BubbleSort;
    QuickSort *quick = new QuickSort;

    // Addition
    my_t->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);

    connect(this, &MainWindow::starting, my_t, /*&MyThread::recvNum*/&MyThread::working);
    connect(ui->start, &QPushButton::clicked, this, [=]() {
        emit starting(1000);
        t1->start();
    });

    connect(my_t, &MyThread::sendArray, bubble, /*&BubbleSort::recvVec*/&BubbleSort::working);
    connect(my_t, &MyThread::sendArray, quick, /*&QuickSort::recvVec*/&QuickSort::working);
    connect(my_t, &MyThread::sendArray, this, [=](QVector<int> vec){
        t2->start();
        // t3->start();
        for (const auto &it : vec) {
            ui->randomList->addItem(QString::number(it));
        }
    });
    connect(bubble, &BubbleSort::finish, this, [=](QVector<int> vec){
        for (const auto &it : vec) {
            ui->bubbleList->addItem(QString::number(it));
        }
    });
    connect(quick, &QuickSort::finish, this, [=](QVector<int> vec){
        for (const auto &it : vec) {
            ui->quickList->addItem(QString::number(it));
        }
    });

    connect(this, &MainWindow::destroyed, this, [=]() {
        // 释放方式2：调用线程的退出函数进行释放
        t2->quit();
        t2->wait();
        t2->deleteLater();

        // 释放方式3：手动调用释放函数
        quick->deleteLater();
    })
}

MainWindow::~MainWindow()
{
    delete ui;
}
