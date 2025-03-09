#ifndef SLIDERDEMO_H
#define SLIDERDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SliderDemo;
}
QT_END_NAMESPACE

class SliderDemo : public QMainWindow
{
    Q_OBJECT

public:
    SliderDemo(QWidget *parent = nullptr);
    ~SliderDemo();

    void actionSliderChangedValue(int value);
private slots:
    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::SliderDemo *ui;
};
#endif // SLIDERDEMO_H
