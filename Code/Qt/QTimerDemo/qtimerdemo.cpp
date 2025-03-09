#include "qtimerdemo.h"
#include "./ui_qtimerdemo.h"

#include <QTime>
#include <QTimer>

QTimerDemo::QTimerDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QTimerDemo)
    , timer_(new QTimer(this))
    , elapsed_(new QElapsedTimer())
{
    ui->setupUi(this);

    timer_->stop();
    timer_->setTimerType(Qt::CoarseTimer);
    ui->normalRadio->setChecked(true);

    connect(timer_, &QTimer::timeout, this, &QTimerDemo::do_timer_timeout);
}

QTimerDemo::~QTimerDemo()
{
    delete ui;
    delete timer_;
    delete elapsed_;
}

void QTimerDemo::do_timer_timeout()
{
    QApplication::beep();
    QTime time = QTime::currentTime();
    ui->hourLCD->display(time.hour());
    ui->minuteLCD->display(time.minute());
    ui->secondLCD->display(time.second());

    if (timer_->isSingleShot()) {
        int pass = elapsed_->elapsed();
        QString str = QString("流逝的时间：%1 毫秒").arg(pass);
        ui->passtimeLabel->setText(str);

        ui->stopBtn->setEnabled(false);
        ui->startBtn->setEnabled(true);
        ui->singleBtn->setEnabled(true);
    }
}

void QTimerDemo::on_startBtn_clicked()
{
    int delay = ui->delaySpin->value();
    bool mode = ui->onceRadio->isChecked();

    timer_->setInterval(delay);
    timer_->setSingleShot(mode);

    if (ui->preciseRadio->isChecked()) timer_->setTimerType(Qt::PreciseTimer);
    else if (ui->normalRadio->isChecked()) timer_->setTimerType(Qt::CoarseTimer);
    else if (ui->crudeRadio->isChecked()) timer_->setTimerType(Qt::VeryCoarseTimer);

    timer_->start();
    elapsed_->restart();

    ui->startBtn->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->singleBtn->setEnabled(false);
}


void QTimerDemo::on_stopBtn_clicked()
{
    int pass = elapsed_->elapsed();
    QString str = QString("流逝的时间：%1 毫秒").arg(pass);
    ui->passtimeLabel->setText(str);

    timer_->stop();

    ui->stopBtn->setEnabled(false);
    ui->startBtn->setEnabled(true);
    ui->singleBtn->setEnabled(true);
}


void QTimerDemo::on_singleBtn_clicked()
{
    int intv = ui->delaySpin->value();
    Qt::TimerType type;

    if (ui->preciseRadio->isChecked())     type = Qt::PreciseTimer;
    else if (ui->normalRadio->isChecked()) type = Qt::CoarseTimer;
    else if (ui->crudeRadio->isChecked())  type = Qt::VeryCoarseTimer;

    QTimer::singleShot(intv, type, this, &QTimerDemo::do_timer_timeout);

    timer_->setSingleShot(true);
    elapsed_->restart();

    ui->startBtn->setEnabled(false);
    ui->stopBtn->setEnabled(true);
    ui->singleBtn->setEnabled(false);
}

