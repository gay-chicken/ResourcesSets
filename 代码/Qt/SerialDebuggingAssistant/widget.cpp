#include "widget.h"
#include "./ui_widget.h"

#include <QSerialPortInfo>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &Widget::ready_ReadSerialData);

    ui->setupUi(this);
    this->setLayout(ui->globalLayout);

    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    for (auto &serialInfo : serialPorts) {
        ui->serialPort->addItem(serialInfo.portName());
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnSerialSwitch_clicked()
{
    // if (ui->serialPort->currentIndex() == -1) {
    //     qDebug() << "Not found Device!";
    //     return;
    // }

    serial->setPortName(ui->serialPort->currentText());
    serial->setBaudRate(ui->baudRate->currentText().toInt());
    serial->setDataBits(QSerialPort::DataBits(
        ui->dataBit->currentText().toInt()));

    // 停止位
    switch(ui->stopBit->currentIndex()) {
    case 0:
        serial->setStopBits(QSerialPort::StopBits::OneStop);
        break;
    case 1:
        serial->setStopBits(QSerialPort::StopBits::OneAndHalfStop);
        break;
    case 2:
        serial->setStopBits(QSerialPort::StopBits::TwoStop);
        break;
    default:
        QCoreApplication::exit(EXIT_FAILURE);
    }

    // 流控
    switch(ui->flowControl->currentIndex()) {
    case 0:
        serial->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
        break;
    case 1:
        serial->setFlowControl(QSerialPort::FlowControl::HardwareControl);
        break;
    case 2:
        serial->setFlowControl(QSerialPort::FlowControl::SoftwareControl);
        break;
    default:
        QCoreApplication::exit(EXIT_FAILURE);
    }

    // 校验位
    switch(ui->checkBit->currentIndex()) {
    case 0:
        serial->setParity(QSerialPort::Parity::NoParity);
        break;
    case 1:
        serial->setParity(QSerialPort::Parity::EvenParity);
        break;
    case 2:
        serial->setParity(QSerialPort::Parity::MarkParity);
        break;
    case 3:
        serial->setParity(QSerialPort::Parity::OddParity);
        break;
    case 4:
        serial->setParity(QSerialPort::Parity::SpaceParity);
        break;
    default:
        QCoreApplication::exit(EXIT_FAILURE);
    }

    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Failed: " << serial->error();
        qDebug() << "[status]"
                 << "port: " << serial->portName()
                 << ", baud rate: " << serial->baudRate()
                 << ", data bit: " << serial->dataBits()
                 << ", parity bit: " << serial->parity()
                 << ", stop bit: " << serial->stopBits()
                 << ", flow ctrl: " << serial->flowControl()
                 << "";
    }
}


void Widget::on_btnSend_clicked()
{
    if (!serial->isOpen()) return;

    static int writeCnt = 0;
    const char* context;

    context = ui->editTextContext->text().toStdString().c_str();
    writeCnt += serial->write(context);
    ui->recordText->append(context);-
    ui->labelStatus->setText("Send OK!");
    ui->labelSentCount->setText(QString("Sent: %1").arg(writeCnt));
}

void Widget::ready_ReadSerialData()
{
    static int readCnt = 0;
    QString context = serial->readAll();

    if (!context.isEmpty()) {
        readCnt += context.size();
        ui->recivedText->append(context);
        ui->labelReceivedCount->setText(QString("Received: %1").arg(readCnt));
    }
}

