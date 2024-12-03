#ifndef SELFBUTTON_H
#define SELFBUTTON_H

#include <QWidget>

class SelfButton : public QWidget
{
    Q_OBJECT
public:
    explicit SelfButton(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void clicked(bool checked = false);
private:
    QPixmap pic;
};

#endif // SELFBUTTON_H
