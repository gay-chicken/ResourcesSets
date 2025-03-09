#include "spinboxdemo.h"
#include "./ui_spinboxdemo.h"

SpinBoxDemo::SpinBoxDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpinBoxDemo)
{
    ui->setupUi(this);
    ui->perSpin->setDecimals(1);
    connect(ui->numberSpin, &QSpinBox::valueChanged, this, &SpinBoxDemo::on_calBtn_clicked);
    connect(ui->perSpin, &QDoubleSpinBox::valueChanged, this, &SpinBoxDemo::on_calBtn_clicked);
    connect(ui->binSpin, &QSpinBox::valueChanged, this, &SpinBoxDemo::actionValueChanged);
    connect(ui->octSpin, &QSpinBox::valueChanged, this, &SpinBoxDemo::actionValueChanged);
    connect(ui->decSpin, &QSpinBox::valueChanged, this, &SpinBoxDemo::actionValueChanged);
    connect(ui->hexSpin, &QSpinBox::valueChanged, this, &SpinBoxDemo::actionValueChanged);
    SpinBoxDemo::on_calBtn_clicked();
}

SpinBoxDemo::~SpinBoxDemo()
{
    delete ui;
}

void SpinBoxDemo::on_calBtn_clicked()
{
    int num = ui->numberSpin->value();
    float price = ui->perSpin->value();
    float total = num * price;
    ui->totalSpin->setValue(total);
}


void SpinBoxDemo::actionValueChanged(int arg1)
{
    ui->binSpin->setValue(arg1);
    ui->decSpin->setValue(arg1);
    ui->octSpin->setValue(arg1);
    ui->hexSpin->setValue(arg1);
}

