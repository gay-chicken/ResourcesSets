#ifndef SPINBOXDEMO_H
#define SPINBOXDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SpinBoxDemo;
}
QT_END_NAMESPACE

class SpinBoxDemo : public QMainWindow
{
    Q_OBJECT

public:
    SpinBoxDemo(QWidget *parent = nullptr);
    ~SpinBoxDemo();

    void actionValueChanged(int arg1);
private slots:
    void on_calBtn_clicked();

private:
    Ui::SpinBoxDemo *ui;
};
#endif // SPINBOXDEMO_H
