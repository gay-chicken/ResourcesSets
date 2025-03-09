#ifndef DATETIMEDEMO_H
#define DATETIMEDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DateTimeDemo;
}
QT_END_NAMESPACE

class DateTimeDemo : public QMainWindow
{
    Q_OBJECT

public:
    DateTimeDemo(QWidget *parent = nullptr);
    ~DateTimeDemo();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::DateTimeDemo *ui;
};
#endif // DATETIMEDEMO_H
