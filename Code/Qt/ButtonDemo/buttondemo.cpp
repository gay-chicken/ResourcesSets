#include "buttondemo.h"
#include "./ui_buttondemo.h"

ButtonDemo::ButtonDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ButtonDemo)
{
    ui->setupUi(this);
    fontsize_ = ui->lineEdit->font().pointSize();
}

ButtonDemo::~ButtonDemo()
{
    delete ui;
}

void ButtonDemo::on_pushButton_4_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignLeft);
}


void ButtonDemo::on_pushButton_6_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignRight);
}


void ButtonDemo::on_pushButton_5_clicked()
{
    ui->lineEdit->setAlignment(Qt::AlignCenter);
}


void ButtonDemo::on_pushButton_2_clicked()
{
    if (fontsize_ > 0) fontsize_--;
    QFont font = ui->lineEdit->font();
    font.setPointSize(fontsize_);
    ui->lineEdit->setFont(font);
}


void ButtonDemo::on_pushButton_3_clicked()
{
    if (fontsize_ < 24) fontsize_++;
    QFont font = ui->lineEdit->font();
    font.setPointSize(fontsize_);
    ui->lineEdit->setFont(font);
}


void ButtonDemo::on_pushButton_clicked()
{
    fontsize_ = 15;
    QFont font = ui->lineEdit->font();
    font.setPointSize(fontsize_);
    ui->lineEdit->setFont(font);
}




void ButtonDemo::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{

}


void ButtonDemo::on_radioButton_clicked()
{
    QPalette palette = ui->lineEdit->palette();
    palette.setColor(QPalette::Text, Qt::red);
    ui->lineEdit->setPalette(palette);
}


void ButtonDemo::on_radioButton_2_clicked()
{
    QPalette palette = ui->lineEdit->palette();
    palette.setColor(QPalette::Text, Qt::black);
    ui->lineEdit->setPalette(palette);
}


void ButtonDemo::on_radioButton_3_clicked()
{
    QPalette palette = ui->lineEdit->palette();
    palette.setColor(QPalette::Text, Qt::green);
    ui->lineEdit->setPalette(palette);
}


void ButtonDemo::on_checkBox_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setBold(checked);
    ui->lineEdit->setFont(font);
}


void ButtonDemo::on_checkBox_2_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setItalic(checked);
    ui->lineEdit->setFont(font);
}


void ButtonDemo::on_checkBox_3_clicked(bool checked)
{
    QFont font = ui->lineEdit->font();
    font.setUnderline(checked);
    ui->lineEdit->setFont(font);
}

