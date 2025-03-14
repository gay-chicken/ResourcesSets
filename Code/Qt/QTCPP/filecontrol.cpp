#include <QDir>
#include <QFile>
#include <QString>

#include "filecontrol.h"

FileControl::FileControl(QObject *parent)
    : QObject{parent}
{}

void FileControl::setText(const QString &text)
{
    if (text != this->text_) {
        this->text_ = text;
        emit textChanged(text);
    }
}

bool FileControl::store()
{
    QFile file(QDir::home().absoluteFilePath("output.txt"));
    if (!file.open(QIODevice::WriteOnly)) return false;

    QTextStream stream(&file);
    stream << "hello, world!";
    file.close();
    return true;
}
