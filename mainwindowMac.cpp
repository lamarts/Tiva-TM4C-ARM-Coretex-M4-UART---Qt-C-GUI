// This file is used only for Mac as it identifies the vendor id and product id for the COMM Port
// See readme
////////////////////////////////////////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QtWidgets>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    arm_port_is_available = false;
    arm_portname = "";

    // Find the number of available ports, the vendor id and product id of each available port
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        qDebug() << "has Vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier())
        {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "has Product ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasProductIdentifier())
        {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
    //  Found the available ports, associated vendor id and product id
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == found_vendorID){
                if(serialPortInfo.productIdentifier() == found_productID){
                    arm_portname = serialPortInfo.portName();
                    arm_port_is_available = true;
                }
            }
        }
    }
    if(arm_port_is_available)
    {
        // Open and configure the serialport
        // Settings for desired port to connect ARM TM4C
        serial->setPortName(arm_portname);
        serial->open(QSerialPort::WriteOnly);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadWrite);
    }
    else
    {
        // Display error message
        QMessageBox::warning(this, "Port Error", "Couldn't find the ARM TM4C");
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LEDControl(QString command)
{
    if(serial->isWritable())
    {
        serial->write(command.toStdString().c_str());
    }
    else
    {
        QMessageBox::warning(this, "Port effort", "Could not find the Tiva Arm device");
    }
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow::LEDControl("r");
}

void MainWindow::on_BluePushbutton_2_clicked()
{
    MainWindow::LEDControl("b");
}

void MainWindow::on_GreenPushButton_3_clicked()
{
    MainWindow::LEDControl("g");
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow::LEDControl("o");
}
