#ifndef QTIMERDEMO_H
#define QTIMERDEMO_H

#include <QMainWindow>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class QTimerDemo;
class QTimer;
class QElapsedTimer;
}
QT_END_NAMESPACE

class QTimerDemo : public QMainWindow
{
    Q_OBJECT

public:
    QTimerDemo(QWidget *parent = nullptr);
    ~QTimerDemo();

private:
    Ui::QTimerDemo *ui;
    QTimer *timer_;
    QElapsedTimer *elapsed_;

private slots:
    void do_timer_timeout();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();
    void on_singleBtn_clicked();
};
#endif // QTIMERDEMO_H
