#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <motor.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();

    Motor *motors;

private slots:
    void on_checkBox_Calibration_Control_toggled(bool checked);

    void on_pushButton_Test_Motor_released();

    void on_pushButton_Connect_released();

    void on_pushButton_Stop_Test_released();

    void on_pushButton_Save_released();

    void on_spinBox_Motor_Slot_valueChanged(int arg1);

    void on_pushButton_Disconnect_released();

    void on_pushButton_clicked();

signals:
    void newValues(int* vals);
    void changeControl(bool gui);
    void tryConnect();
    void disconnect();
    void changeMotorSetting(int slot, QString motorID, bool inverse);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
