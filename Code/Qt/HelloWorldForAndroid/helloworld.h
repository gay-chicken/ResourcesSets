#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <QMainWindow>
#include <QTouchEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Helloworld;
}
QT_END_NAMESPACE

class Helloworld : public QMainWindow
{
    Q_OBJECT

public:
    Helloworld(QWidget *parent = nullptr);
    ~Helloworld();

protected:
    bool event(QEvent *event) override;

private:
    Ui::Helloworld *ui;
};
#endif // HELLOWORLD_H
