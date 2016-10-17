#include "motor.h"

Motor::Motor()
{

}

QString Motor::getCode() const{
    switch (code) {
    case HLB:
        return "HLB";
    case HLF:
        return "HLF";
    case HRB:
        return "HRB";
    case HRF:
        return "HRF";
    case VB:
        return "VB";
    case VF:
        return "VF";
    case VL:
        return "VL";
    case VR:
        return "VR";
    }
}

void Motor::setCode(QString code) {
    if (!code.compare("HLB")) {
        this->code = HLB;
        return;
    }
    if (!code.compare("HLF")) {
        this->code = HLF;
        return;
    }
    if (!code.compare("HRB")) {
        this->code = HRB;
        return;
    }
    if (!code.compare("HRF")) {
        this->code = HRF;
        return;
    }
    if (!code.compare("VB")) {
        this->code = VB;
        return;
    }
    if (!code.compare("VF")) {
        this->code = VF;
        return;
    }
    if (!code.compare("VL")) {
        this->code = VL;
        return;
    }
    if (!code.compare("VR")) {
        this->code = VR;
        return;
    }
}
