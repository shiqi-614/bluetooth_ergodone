#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "KeyboardHost.h"
#include "MouseReport.h"

class Joystick {
public:
    Joystick();
    void begin(KeyboardHost& host);
    report_mouse_t handleJoystick();

private:
    KeyboardHost* _host;
    bool need_send;
    int btn_state;
    int btn_read_state;
    unsigned long btn_current_action_time;
    unsigned long btn_last_action_time;
    uint16_t joystick_repeat;
    uint16_t last_timer;
    report_mouse_t mouse_report;
};

#endif
