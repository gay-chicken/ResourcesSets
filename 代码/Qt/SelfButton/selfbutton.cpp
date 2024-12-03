#include "selfbutton.h"

#include <QPainter>

SelfButton::SelfButton(QWidget *parent)
    : QWidget{parent}
{
    pic.load(":/icon/dakai.png");
    setFixedSize(pic.size());
    update();
}

void SelfButton::mousePressEvent(QMouseEvent *event)
{
    pic.load(":/icon/guanbi.png");
    emit clicked();
}

void SelfButton::enterEvent(QEnterEvent *event)
{
    pic.load(":/icon/baocun.png");
    update();
}

void SelfButton::leaveEvent(QEvent *event)
{
    pic.load(":/icon/dakai.png");
    update();
}

void SelfButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), pic);
}
