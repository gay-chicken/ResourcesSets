#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QVector>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    void sendArray(QVector<int> &);

public slots:
    void recvNum(int num);

private:
    int num_;
};

#endif // MYTHREAD_H
