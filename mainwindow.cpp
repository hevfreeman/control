#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::init() {
    on_spinBox_Motor_Slot_valueChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_Calibration_Control_toggled(bool checked)
{
    emit changeControl(checked);
}

void MainWindow::on_pushButton_Test_Motor_released()
{
    int* vals = new int[8];
    if (ui->checkBox_Calibration_Control->isChecked()) {
        for (int i = 0; i < 8; ++i)
            motors[i].speed = 0;
            //vals[i] = 0;
        int currentSlot = ui->spinBox_Motor_Slot->text().toInt();
        int currentSpeed = ui->spinBox_Motor_Speed->text().toInt();
        motors[currentSlot].speed = currentSpeed;
        emit newValues(vals);
    }
}


void MainWindow::on_pushButton_Connect_released()
{
    emit tryConnect();
}



void MainWindow::on_pushButton_Stop_Test_released()
{
    int* vals = new int[8];
    if (ui->checkBox_Calibration_Control->isChecked()) {
        for (int i = 0; i < 8; ++i)
            motors[i].speed = 0;
    }
}

void MainWindow::on_pushButton_Save_released()
{
    int code = ui->spinBox_Motor_Slot->value();
    motors[code].enabled = ui->checkBox_Enabled->isChecked();
    motors[code].inverse = ui->checkBox_Inverse->isChecked();
    motors[code].k_backward = ui->doubleSpinBox_back->value();
    motors[code].k_forward = ui->doubleSpinBox_forw->value();
    motors[code].setCode(ui->comboBox_Tested_Motor->currentText());

    // TODO Refactor method
    emit changeMotorSetting(ui->spinBox_Motor_Slot->value(),
                            ui->comboBox_Tested_Motor->currentText(),
                            ui->checkBox_Inverse->isChecked());
}

void MainWindow::on_spinBox_Motor_Slot_valueChanged(int code)
{
    ui->checkBox_Enabled->setChecked(motors[code].enabled);
    ui->checkBox_Inverse->setChecked(motors[code].inverse);

    ui->doubleSpinBox_back->setValue(motors[code].k_backward);
    ui->doubleSpinBox_forw->setValue(motors[code].k_forward);

    ui->comboBox_Tested_Motor->setCurrentText(motors[code].getCode());
}

void MainWindow::on_pushButton_Disconnect_released()
{
    emit disconnect();
}

void MainWindow::on_pushButton_clicked()
{
    Dialog *dialog = new Dialog();
    dialog->decorate();
    dialog->show();
}
