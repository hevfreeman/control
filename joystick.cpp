#include "joystick.h"


Joystick::Joystick(QObject *parent) : QObject(parent)
{

}

bool Joystick::init(int joystick_id) {
    sf::Joystick::update();
    if (sf::Joystick::isConnected(joystick_id)) {
        this->joystick_id = joystick_id;
        return true;
    } else {
        return false;
    }
}


void Joystick::update() {
    sf::Joystick::update();
    this->axis_pitch = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::PovY);
    this->axis_roll  = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::PovX);
    this->axis_yaw   = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::R);

    this->axis_front = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::Y);
    this->axis_side  = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::X);
    this->axis_depth = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::Z);


    this->axis_light = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::U);

    this->axis_sensitivity = +
        sf::Joystick::getAxisPosition(joystick_id, sf::Joystick::V);

    this->btn_depth_inv   = sf::Joystick::isButtonPressed(joystick_id,  SFML_BTN_DEPTH_INV);
    this->btn_grab        = sf::Joystick::isButtonPressed(joystick_id,  SFML_BTN_GRAB);
    this->btn_grab_strong = sf::Joystick::isButtonPressed(joystick_id,  SFML_BTN_GRAB_STRONG);
    this->btn_ungrab      = sf::Joystick::isButtonPressed(joystick_id,  SFML_BTN_UNGRAB);


    std::cout << "a_pitch=" << axis_pitch << " a_roll=" << axis_roll << " a_yaw="   << axis_yaw   << std::endl;
    std::cout << "a_front=" << axis_front << " a_side=" << axis_side << " a_depth=" << axis_depth << std::endl;
    std::cout << "a_light=" << static_cast<int16_t>(axis_light)
              << " a_grub=" << btn_grab << std::endl
              << "a_sensitivity=" << axis_sensitivity
              << std::endl;
}

void Joystick::printButtons() {
    for (int i = 0; i<=sf::Joystick::ButtonCount; i++) {
        if (sf::Joystick::isButtonPressed(joystick_id, i))
            std::cout << "BUTTON " << i << std::endl;
    }
}
