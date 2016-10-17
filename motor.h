#ifndef MOTOR_H
#define MOTOR_H
#include <stdint.h>
#include <QString>

class Motor
{
public:
    Motor();

    enum MotorCode {
        HLB, HLF, HRB, HRF, VB, VF, VL, VR
    };

    MotorCode code;
    uint8_t adress; // 0..7
    int16_t speed;  // -32 768..+32 767
    bool inverse;
    bool enabled;

    double k_forward;
    double k_backward;



    QString getCode() const;
    void setCode(QString code);
};

#endif // MOTOR_H
