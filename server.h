#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QSerialPort>
#include <QTest>
#include <qtimer.h>
#include <stdint.h>
#include <messages.h>
#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib>

#include "joystick.h"
#include "motor.h"


#define REQUEST_DELAY					50
#define REQUEST_TIMEOUT					50


struct Message {
    int16_t yaw   = 0;
    int16_t pitch = 0;
    int16_t marsh = 0;
    int16_t lag   = 0;
    int16_t depth = 0;

    int8_t grub1  = 0;
    int8_t grub2  = 0;
    int8_t light  = 0;
    int8_t tilt   = 0;
    int8_t dev1   = 0;
    int8_t dev2   = 0;
    int8_t flags1 = 0;
    int8_t flags2 = 0;

    int16_t VF    = 0;
    int16_t VR    = 0;
    int16_t VB    = 0;
    int16_t VL    = 0;
    int16_t HRF   = 0;
    int16_t HRB   = 0;
    int16_t HLB   = 0;
    int16_t HLF   = 0;
};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();
    Motor* motors;

private:
    QTimer *sendTimer;
    QSerialPort *newPort;

    Message m;
    Joystick j;

    float sensitivity;

    bool overrideAllSettings = false;

    void writeMotor(Motor motor, uint8_t *msg_to_send);

    bool COMconnect(int com_name);
    void addCheckSumm16b(uint8_t * msg, uint16_t length);

    int16_t translateCoords(float joy, float from_start, float from_end, int to_start, int to_end);
    float translateCoords(float joy, float from_start, float from_end, float to_start, float to_end);
signals:

public slots:
    void sendMessage();
    void connect_com();
    void disconnect_com();

    void setControl(bool gui);
};

#endif // SERVER_H
