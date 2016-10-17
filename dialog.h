#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void decorate();
    void sl(bool yaw_sl, bool roll_sl, bool pitch_sl, bool depth_sl);
    void temperature(int16_t temperature);
    void horizon(int16_t horizon);
    void motor(int16_t VF,
               int16_t VR,
               int16_t VB,
               int16_t VL,
               int16_t HRF,
               int16_t HRB,
               int16_t HLB,
               int16_t HLF);
    void depth(int16_t depth);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
