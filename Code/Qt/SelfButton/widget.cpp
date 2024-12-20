#include "widget.h"
#include "selfbutton.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->selfbutton, &SelfButton::clicked, [=](){
        qDebug() << "SelfButton clicked!";
    });
    // ui->selfbutton->installEventFilter(this);
    this->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Wheel) {
        qDebug() << "wheel";
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
        if (mouse->button() == Qt::LeftButton) {
            qDebug() << "Left Button Double Clicked!";
        } else if (mouse->button() == Qt::RightButton) {
            qDebug() << "Right Button Double Clicked!";
        }
    }
}




