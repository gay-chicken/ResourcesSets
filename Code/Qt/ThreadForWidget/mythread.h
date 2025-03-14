#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QVector>
#include <QThread>
#include <QObject>

class MyThread : public /*QThread*/ QObject // Addition
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
/*
protected:
    void run() override;
*/
    void working(int num); // Addition
/*
private:
    int num_;

public slots:
    void recvNum(int num);
*/
signals:
    void sendArray(QVector<int>);
};

class BubbleSort : public /*QThread*/ QObject // Addition
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
/*
protected:
    void run() override;
*/
    void working(QVector<int> vec); // Addition
/*
public slots:
    void recvVec(QVector<int>);
*/
signals:
    void finish(QVector<int>);
/*
private:
    QVector<int> vec_;
*/
};

class QuickSort : public /*QThread*/ QObject // Addition
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    QuickSort(const QVector<int> &vec, QObject *parent = nullptr);
/*
protected:
    void run() override;
*/
    void working(QVector<int> vec); // Addition
/*
public slots:
    void recvVec(QVector<int>);
*/
signals:
    void finish(QVector<int>);
/*
private:
    QVector<int> vec_;
*/
};

#endif // MYTHREAD_H
