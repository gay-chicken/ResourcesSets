#include "helloworld.h"
#include "./ui_helloworld.h"

#include <QScreen>
#include <QTouchEvent>
#include <QPointF>

Helloworld::Helloworld(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Helloworld)
{
    ui->setupUi(this);

    // 获取屏幕大小
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize size = screen->geometry().size();
    qreal scale = screen->devicePixelRatio();
    ui->lineEdit->setText(QString::number(size.width()));
    ui->lineEdit_2->setText(QString::number(size.height()));
    ui->lineEdit_3->setText(QString::number(scale));

    // 获取触摸事件
    this->setAttribute(Qt::WA_AcceptTouchEvents);
}

Helloworld::~Helloworld()
{
    delete ui;
}

bool Helloworld::event(QEvent *event)
{
    if (event->type() != QEvent::TouchBegin &&
        event->type() != QEvent::TouchUpdate &&
        event->type() != QEvent::TouchEnd) {
        return QWidget::event(event);
    }

    static QMap<QEvent::Type, QString> opers = {
                                                {QEvent::TouchBegin, "开始触摸"},
                                                {QEvent::TouchUpdate, "拖动"},
                                                {QEvent::TouchEnd, "离开屏幕"}};

    event->accept();
    QTouchEvent *touchEvent = static_cast<QTouchEvent*>(event);
    QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->points();

    if (touchPoints.isEmpty()) return true;

    auto opt = opers.find(event->type());
    ui->lineEdit_6->setText(opt == opers.end() ? "未知操作" : opt.value());

    for (int i = 0; i < touchPoints.size(); i++) {
        QTouchEvent::TouchPoint point = touchPoints.at(i);
        QPointF pos = point.lastPosition();
        ui->lineEdit_4->setText(QString::number(pos.rx()));
        ui->lineEdit_5->setText(QString::number(pos.ry()));
        ui->lineEdit_7->setText(QString::number(point.pressure()));
    }


    return true;
}
