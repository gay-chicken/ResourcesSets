#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <windows.h>
#include <iostream>
#include <string>
#include <map>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void KeyClickHandle(INPUT *input, int pretime, int reltime);

private slots:
    void on_globalKey_clicked();

private:
    Ui::Widget *ui;
    std::unordered_map<QString, DWORD> keys;
    bool status;
};
#endif // WIDGET_H
