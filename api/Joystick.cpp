#include "Joystick.h"
#include "Arduino.h"
#include <Mouse.h>

Joystick::Joystick()
{
}

void Joystick::begin(KeyboardHost& host)
{
    _host = &host;
    joystick_repeat = 0;
    mouse_report = {};

    pinMode(JOYSTICK_BUTTON_PIN, INPUT_PULLUP);
    dprintf("joystick begin\n");
}

int readAxis(int pin)
{
    int reading = analogRead(pin);
    reading = map(reading, 0, 1023, 0, JOYSTICK_MOUSE_SENSITIVITY);
    int distance = reading - (JOYSTICK_MOUSE_SENSITIVITY / 2);
    if (abs(distance) < JONYSTICK_MOUSE_MOVE_THRESHOLD) {
        distance = 0;
    }
    return distance;
}

int8_t getUnit(int value, int joystick_repeat)
{
    if (value == 0)
        return 0;
    double unit = ((value * MOUSEKEY_MAX_SPEED) / JOYSTICK_MOUSE_SENSITIVITY) / JOYSTICK_2_MOUSE_RATIO;
    for (int i = 0; i < joystick_repeat; i++)
        unit *= JONYSTICK_MOVE_EXPONENTIAL_BASE;

    unit = (unit > MOUSEKEY_MAX_SPEED ? MOUSEKEY_MAX_SPEED : unit);
    unit = (unit < -1 * MOUSEKEY_MAX_SPEED ? -1 * MOUSEKEY_MAX_SPEED : unit);
    unit = (unit == 0 ? value > 0 ? 1 : -1 : unit);
    return unit;
}

void Joystick::handleJoystick()
{

    if (timer_elapsed(last_timer) < (joystick_repeat ? MOUSEKEY_INTERVAL : MOUSEKEY_DELAY))
        return;

    need_send = 0;
    int x = readAxis(JOYSTICK_X_PIN) * -1;
    int y = readAxis(JOYSTICK_Y_PIN) * -1;

    if (x || y) {
        need_send = 1;
        joystick_repeat++;
        dprintf("joystick value read from pin x -> %d, y -> %d, repeat -> %d \n", x, y, joystick_repeat);

        mouse_report.x = getUnit(x, joystick_repeat);
        mouse_report.y = getUnit(y, joystick_repeat);

        need_send = 1;
    } else {
        mouse_report.x = 0;
        mouse_report.y = 0;
        joystick_repeat = 0;
    }

    btn_read_state = digitalRead(JOYSTICK_BUTTON_PIN) ^ 1;
    if (btn_read_state != btn_state) {
        btn_current_action_time = millis();
        if (btn_current_action_time - btn_last_action_time > DEBOUNCE) {
            btn_state = btn_read_state;
            btn_last_action_time = btn_current_action_time;
            mouse_report.buttons ^= 1;
            need_send = true;
        }
    }

    if (need_send) {
        MouseReport report(&mouse_report);
        _host->sendMouse(report);
        last_timer = millis();
        dprintf("joystic send mouse event button->%d, x->%d, y->%d\n",
            mouse_report.buttons,
            mouse_report.x,
            mouse_report.y);
    }
}
