#include "sliderdemo.h"
#include "./ui_sliderdemo.h"

SliderDemo::SliderDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SliderDemo)
{
    ui->setupUi(this);
    connect(ui->progressBar, &QProgressBar::valueChanged, this, &SliderDemo::actionSliderChangedValue);
    connect(ui->dial, &QSlider::valueChanged, this, &SliderDemo::actionSliderChangedValue);
    connect(ui->horizontalScrollBar, &QSlider::valueChanged, this, &SliderDemo::actionSliderChangedValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &SliderDemo::actionSliderChangedValue);
}

SliderDemo::~SliderDemo()
{
    delete ui;
}

void SliderDemo::actionSliderChangedValue(int value)
{
    ui->dial->setValue(value);
    ui->horizontalSlider->setValue(value);
    ui->horizontalScrollBar->setValue(value);
    ui->progressBar->setValue(value);
}

void SliderDemo::on_checkBox_clicked(bool checked)
{
    ui->progressBar->setTextVisible(checked);
    ui->groupBox_4->setEnabled(checked);
}


void SliderDemo::on_checkBox_2_clicked(bool checked)
{
    ui->progressBar->setInvertedAppearance(checked);
}


void SliderDemo::on_radioButton_clicked()
{
    ui->progressBar->setFormat("%p%");
}


void SliderDemo::on_radioButton_2_clicked()
{
    ui->progressBar->setFormat("%v");
}

