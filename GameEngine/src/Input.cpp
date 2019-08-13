#include "Input.h"

Input::Input()  {
    this->mouse_pos_x = 0;
    this->mouse_pos_y = 0;
}

Input::~Input() {}

void Input::updateMousePos(int x, int y) {
    this->mouse_pos_x = x;
    this->mouse_pos_y = y;
}

void Input::mousePos(int *x, int *y) {
    x = &this->mouse_pos_x;
    y = &this->mouse_pos_y;
}

void Input::sendKeyDownName(const char *name) {
    LOG(MESSAGE) << "Key Down [" << name << "]";
}

void Input::sendKeyUpName(const char *name) {
    LOG(MESSAGE) << "Key Up [" << name << "]";
}

void Input::sendMouseButtonDownID(int id, int x, int y) {
    this->updateMousePos(x, y);
    switch(id) {
    case M_BUTTON::L_BUTTON:
        LOG(MESSAGE) << "Left Down @[" << x << "X" << y << "]";
        break;
    case M_BUTTON::R_BUTTON:
        LOG(MESSAGE) << "Right Down @[" << x << "X" << y << "]";
        break;
    }
}

void Input::sendMouseButtonUpID(int id, int x, int y) {
    this->updateMousePos(x, y);
    switch(id) {
    case M_BUTTON::L_BUTTON:
        LOG(MESSAGE) << "Left Up @[" << x << "X" << y << "]";
        break;
    case M_BUTTON::R_BUTTON:
        LOG(MESSAGE) << "Right Up @[" << x << "X" << y << "]";
        break;
    }
}