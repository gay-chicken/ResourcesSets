#ifndef BUTTONDEMO_H
#define BUTTONDEMO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ButtonDemo;
}
QT_END_NAMESPACE

class ButtonDemo : public QMainWindow
{
    Q_OBJECT

public:
    ButtonDemo(QWidget *parent = nullptr);
    ~ButtonDemo();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

private:
    Ui::ButtonDemo *ui;
    uint fontsize_;
};
#endif // BUTTONDEMO_H
