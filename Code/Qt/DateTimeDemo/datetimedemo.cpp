#include "datetimedemo.h"
#include "./ui_datetimedemo.h"

DateTimeDemo::DateTimeDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DateTimeDemo)
{
    ui->setupUi(this);

    ui->dateEdit->setDateTime(QDateTime::currentDateTimeUtc());
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTimeUtc());

}

DateTimeDemo::~DateTimeDemo()
{
    delete ui;
}

void DateTimeDemo::on_calendarWidget_clicked(const QDate &date)
{
    qDebug() << date;
}


void DateTimeDemo::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    qDebug() << dateTime;
}


void DateTimeDemo::on_dateEdit_userDateChanged(const QDate &date)
{
    qDebug() << date;
}

