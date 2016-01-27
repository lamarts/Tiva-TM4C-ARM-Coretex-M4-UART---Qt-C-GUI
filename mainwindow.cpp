//  This file is used for Windows implementation only - see readme
//  The COMM Port hardcoded below may be different than yours

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial->setPortName("COM6");                    // Port name
    serial->setBaudRate(QSerialPort::Baud9600);     // Baudrate
    serial->setDataBits(QSerialPort::Data8);        // Data bits
    serial->setParity(QSerialPort::NoParity);       // No Parity
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);



}

MainWindow::~MainWindow()
{
    delete ui;
    if(serial->isOpen())
       serial->close();
}

void MainWindow::LEDControl(QString command)
{
    if(serial->isWritable())
    {
        serial->write(command.toStdString().c_str());
    }
    else
    {
        // qDebug() << "Could not write to serial!";
        QMessageBox::warning(this, "Port error", "Could not find the Tiva ARM device");
    }
}

void MainWindow::on_RedButton_clicked()
{
    MainWindow::LEDControl("r");
}

void MainWindow::on_BlueButton_clicked()
{
    MainWindow::LEDControl("b");

}

void MainWindow::on_GreenButton_clicked()
{
    MainWindow::LEDControl("g");
}


void MainWindow::on_offButton_clicked()
{
    MainWindow::LEDControl("o");
}
