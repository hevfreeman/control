#include "server.h"


const int MAX_COM_ID = 42;
const int MAX_JOYSTICK_ID = 13;
unsigned int DEPTH_BUTTON_ID = 6;

int MIN_ENGINE_POWER = 0;
int MAX_ENGINE_POWER = 256;


// Стандартный для SFML диапазон значений, читаемых с джойстика
float MIN_JOYSTICK_VALUE = -100.;
float MAX_JOYSTICK_VALUE =  100.;


// Диапазон значений, отправляемых на движки
int MIN_VALUE = -255;
int MAX_VALUE = 255;


Server::Server(QObject *parent) : QObject(parent)
{
    sendTimer = new QTimer(this);
    connect(sendTimer, SIGNAL(timeout()), this, SLOT( sendMessage() ));

    newPort = 0;

    bool flag = false;
    for (int i = 0; i < MAX_JOYSTICK_ID; ++i) {
        if (j.init(i)) {
            flag = true;
            break;
        }
    }
    if (!flag)
        std::cout << "No joystick found among ids from 0 to " << MAX_JOYSTICK_ID-1 << std::endl;
    else
        std::cout << "Joystick connected" << std::endl;

    j.update();
}

Server::~Server() {
    std::cout << "Server shutting down..." << std::endl;
    if (newPort && newPort->isOpen()) {
        std::cout << "Stopping motors.." << std::endl;
        uint8_t msg_to_send[REQUEST_MESSAGE_LENGTH];
        for (int i = 0; i < REQUEST_MESSAGE_LENGTH; ++i) {
            msg_to_send[i] = 0x00;
        }
        addCheckSumm16b(msg_to_send, REQUEST_MESSAGE_LENGTH);
        newPort->write((char*)msg_to_send, REQUEST_MESSAGE_LENGTH);
        std::cout << "Success" << std::endl;
        std::cout << "Closing port" << std::endl;
        newPort->close();
        newPort->deleteLater();
    }
    std::cout << "Goodbye!" << std::endl;
}

bool Server::COMconnect(int com_num)
{
    int openFlag;

    QString str = "COM";
    str.append(QString::number(com_num));

    std::cout << "Trying to open port |" << str.toStdString() << "|" << std::endl;

    newPort = new QSerialPort(str);
    newPort->setBaudRate(QSerialPort::Baud57600, QSerialPort::AllDirections);
    newPort->setDataBits(QSerialPort::Data8);
    newPort->setParity(QSerialPort::NoParity);
    newPort->setStopBits(QSerialPort::OneStop);
    newPort->setFlowControl(QSerialPort::NoFlowControl);

    std::cout << "Initializing port COM" << com_num << std::endl;
    try {
        openFlag = newPort->open(QIODevice::ReadWrite);
    } catch(...) {
        std::cout << "Serial port openning error" << std::endl;
        return false;
    }

    if (openFlag) {
        std::cout << "Serial port was successfully opened!" << std::endl;
        sendTimer->start(REQUEST_DELAY);
    } else {
        std::cout << "Cannot open serial port" << std::endl;
        return false;
    }
    return true;
}

void Server::sendMessage()
{
    uint8_t msg_to_send[REQUEST_MESSAGE_LENGTH];
    for (int i = 0; i < REQUEST_MESSAGE_LENGTH; ++i) {
        msg_to_send[i] = 0x00;
    }


    int16_t pitch = 0;
    int16_t roll = 0;
    int16_t yaw = 0;

    int16_t front = 0;
    int16_t side = 0;
    int16_t depth = 0;

    int8_t light = 0;
    int8_t grab = 0;

    sensitivity = 0;
    //int8_t sensitivity = 0;

    if (!overrideAllSettings) {
        j.update();
        pitch = translateCoords(j.axis_pitch, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE,  MIN_VALUE,  MAX_VALUE);
        roll  = translateCoords(j.axis_roll,  MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE,  MIN_VALUE,  MAX_VALUE);
        yaw   = translateCoords(j.axis_yaw,   MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE,  MIN_VALUE,  MAX_VALUE);

        front = translateCoords(j.axis_front, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE, MIN_VALUE, MAX_VALUE);
        side  = translateCoords(j.axis_side,  MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE, MIN_VALUE, MAX_VALUE);
        depth = translateCoords(j.axis_depth, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE, MAX_VALUE,         0);

        light  = translateCoords(j.axis_light, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE, 0, 63);
        sensitivity = translateCoords(j.axis_sensitivity, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE, (float)0, (float)2);
        if (j.btn_depth_inv)
            depth = -depth;

        if      (j.btn_ungrab)
            grab = -200;
        else if (j.btn_grab_strong)
            grab = 200;
        else if (j.btn_grab)
            grab = 200;
        else
            grab = 0;

        std::cout << "pitch=" << pitch << " roll=" << roll << " yaw="   << yaw   << std::endl;
        std::cout << "front=" << front << " side=" << side << " depth=" << depth << std::endl;
        std::cout << "light=" << static_cast<int16_t>(light)
                  << " grub=" << static_cast<int16_t>(grab)
                  << " sensitivity= " << sensitivity
                  << std::endl;

        m.HLB = round((+ front + side - yaw)/3);
        m.HLF = round((- front + side + yaw)/3);
        m.HRB = round((+ front - side + yaw)/3);
        m.HRF = round((- front - side - yaw)/3);

        m.VB  = round((- depth + 0    + pitch));
        m.VF  = round((+ depth + 0    + pitch));
        m.VL  = round((- depth + roll + 0    ));
        m.VR  = round((- depth - roll + 0    ));

        std::cout << "HLB= " << m.HLB << std::endl;
        std::cout << "HLF= " << m.HLF << std::endl;
        std::cout << "HRB= " << m.HRB << std::endl;
        std::cout << "HRF= " << m.HRF << std::endl;

        std::cout << "VB = " << m.VB  << std::endl;
        std::cout << "VF = " << m.VF  << std::endl;
        std::cout << "VL = " << m.VL  << std::endl;
        std::cout << "VR = " << m.VR  << std::endl;
    } else {
        light = 0;
        grab = 0;

        pitch = 0;
        roll = 0;
        yaw = 0;

        front = 0;
        side = 0;
        depth = 0;
    }


    msg_to_send[NORMAL_MODE_MESSAGE_GRUB1]      = light;
    msg_to_send[NORMAL_MODE_MESSAGE_LIGHT]      = grab;
    msg_to_send[NORMAL_MODE_MESSAGE_FLAGS1]     = 0x0f;
    msg_to_send[NORMAL_MODE_MESSAGE_FLAGS2]     = 0xf0;


    for (int i = 0; i < 8; ++i) {
        writeMotor(motors[i], msg_to_send);
    }

    addCheckSumm16b(msg_to_send, REQUEST_MESSAGE_LENGTH);


    /*for (int i = 0; i < REQUEST_MESSAGE_LENGTH; ++i) {
        std::cout << "|N" << i << "=" << unsigned(msg_to_send[i]) << std::endl;
    }*/

    newPort->write((char*)msg_to_send, REQUEST_MESSAGE_LENGTH);

    QTest::qSleep (REQUEST_TIMEOUT);

    ///////////////////////////////////////////////////////////////////RECEIVING MESSAGE HERE//////////////////////////////////////////////////////////////////
    if (newPort->bytesAvailable()){
        QByteArray msg_in = newPort->readAll();
        std::cout << "Got response " << msg_in[0] << std::endl;
    }
    //////////////////////////////////////////////////////////////////END OF RECEIVING MESSAGE/////////////////////////////////////////////////////////////////
}

int16_t Server::translateCoords(float joy, float from_start, float from_end, int to_start, int to_end) {
    float val_from_zero_to_one = (joy - from_start) / (from_end - from_start);
    float ans = val_from_zero_to_one * (to_end - to_start) + to_start;
    return round(ans);
}

float Server::translateCoords(float joy, float from_start, float from_end, float to_start, float to_end) {
    float val_from_zero_to_one = (joy - from_start) / (from_end - from_start);
    float ans = val_from_zero_to_one * (to_end - to_start) + to_start;
    return ans;
}

void Server::addCheckSumm16b(uint8_t * msg, uint16_t length)
{
    uint16_t crc = 0;
    int i = 0;

    for(i=0; i < length - 2; i++){
        crc = (uint8_t)(crc >> 8) | (crc << 8);
        crc ^= msg[i];
        crc ^= (uint8_t)(crc & 0xff) >> 4;
        crc ^= (crc << 8) << 4;
        crc ^= ((crc & 0xff) << 4) << 1;
    }

    msg[length-2] = (uint8_t) (crc >> 8);
    msg[length-1] = (uint8_t) crc;
}



void Server::setControl(bool gui)
{
    overrideAllSettings = gui;
}


void Server::writeMotor(Motor motor, uint8_t * msg_to_send) {
    int adress = 18 + motor.adress*2;
    int16_t speed = 0;

    if (!motor.enabled) {
        msg_to_send[adress] = 0;
        std::cout << motor.getCode().toStdString()  << " motor is not enabled" << std::endl;
        return;
    }

    if (overrideAllSettings) {
        speed = motor.speed;
    } else {
        switch (motor.code) {
        case motor.HLB:
            speed = m.HLB;
            break;
        case motor.HLF:
            speed = m.HLF;
            break;
        case motor.HRB:
            speed = m.HRB;
            break;
        case motor.HRF:
            speed = m.HRF;
            break;
        case motor.VB:
            speed = m.VB;
            break;
        case motor.VF:
            speed = m.VF;
            break;
        case motor.VL:
            speed = m.VL;
            break;
        case motor.VR:
            speed = m.VR;
            break;
        }

        speed = round(speed*sensitivity);

        if (speed < 0) {
            speed = round(speed * motor.k_backward);
        } else if (speed > 0) {
            speed = round(speed * motor.k_forward);
        }

        if (motor.inverse)
            speed = -speed;        
    }

    msg_to_send[adress+1] = speed;
    msg_to_send[adress] = speed >> 8;
}



void Server::connect_com()
{
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //std::cout << "Warning! Overriding COM port!" << std::endl;

    sendTimer->start(300);
    for (int i = 0; i < MAX_COM_ID; ++i) {
        if (COMconnect(i)){
            break;
        }
    }
}

void Server::disconnect_com() {
    std::cout << "Disconnecting" << std::endl;
}


