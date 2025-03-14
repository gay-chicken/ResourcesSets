#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY update FINAL)

public:
    explicit Calculator(QObject *parent = nullptr) : QObject{parent} {}

    const QString &text() { return this->result_; }

    Q_INVOKABLE void calculate(const QString &x, const QString &y){
        bool ok1, ok2;
        double a = x.toDouble(&ok1);
        double b = y.toDouble(&ok2);

        if (ok1 && ok2) {
            this->result_ = QString::number(a + b);
        } else {
            this->result_ = "Error";
        }
        emit update();
    }

private:
    QString result_;

signals:
    void update();
};

#endif // CALCULATOR_H
