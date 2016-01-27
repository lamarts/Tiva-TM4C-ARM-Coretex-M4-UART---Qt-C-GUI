// Windows implementation only

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

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
    void on_RedButton_clicked();
    void on_BlueButton_clicked();
    void on_GreenButton_clicked();
    void on_offButton_clicked();


protected:


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
