#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QObject>

class FileControl : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged FINAL)

public:
    explicit FileControl(QObject *parent = nullptr);

    void setText(const QString &text);
    const QString &text() { return this->text_; }

    Q_INVOKABLE bool store();
private:
    QString text_;

signals:
    void textChanged(const QString &text);
};

#endif // FILECONTROL_H
