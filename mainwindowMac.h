#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void LEDControl(QString);
    void on_pushButton_clicked();
    void on_BluePushbutton_2_clicked();
    void on_GreenPushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    static const quint16 found_vendorID = 7358;
    static const quint16 found_productID = 253;
    QString arm_portname;
    bool arm_port_is_available;
};

#endif // MAINWINDOW_H
