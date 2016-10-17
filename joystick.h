#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <iostream>
#include <SFML/Window.hpp>

class Joystick : public QObject
{
    Q_OBJECT
public:
    float axis_pitch       = 0.0;
    float axis_roll        = 0.0;
    float axis_yaw         = 0.0;

    float axis_front       = 0.0;
    float axis_side        = 0.0;
    float axis_depth       = 0.0;

    float axis_light       = 0.0;
    float axis_sensitivity = 0.0;

    bool btn_depth_inv   = false;  // 6
    bool btn_grab        = false;  // 0
    bool btn_grab_strong = false;  // 14
    bool btn_ungrab      = false;  // 5


    explicit Joystick(QObject *parent = 0);
    bool init(int joystick_id);
    void update();
    void printButtons();

private:
    const int SFML_BTN_DEPTH_INV   = 6;
    const int SFML_BTN_GRAB        = 0;
    const int SFML_BTN_GRAB_STRONG = 14;
    const int SFML_BTN_UNGRAB      = 5;

    int joystick_id = 0;



signals:

public slots:

};

#endif // JOYSTICK_H
