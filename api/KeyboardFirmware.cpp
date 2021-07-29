#include "KeyboardFirmware.h"
#include "gluecode.h"

static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t* report);
static void send_mouse(report_mouse_t* report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

static host_driver_t _global_host_driver = {
    keyboard_leds,
    send_keyboard,
    send_mouse,
    send_system,
    send_consumer
};

static bool _global_host_driver_set = false;

extern "C" int8_t arduino_tmk_sendchar(uint8_t c)
{
    if (debug_enable) {
        return Serial.write(c);
    } else {
        return 0;
    }
}

KeyboardFirmware_::KeyboardFirmware_()
{
}

void KeyboardFirmware_::begin(KeyboardHost& host, KeyboardMatrix& matrix)
{
    dprintf("keyboard firmware begin\n");

    timer_init();
    led_status = 0;

    _host = &host;
    _matrix = &matrix;
    _host->begin();
    _matrix->begin();

    if (!_global_host_driver_set) {
        dprintf("setting global host driver\n");
        host_set_driver(&_global_host_driver);
    }

#ifdef JOYSTICK_ENABLE
    joystick.begin(host);
    dprintf("joystick enable.\n");
#endif

    dprintf("keyboard firmware begin end\n");
}

void KeyboardFirmware_::runTask()
{
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    _matrix->scan();

    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = _matrix->getRow(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        matrix_row_t col_mask = 1;
        for (uint8_t c = 0; c < MATRIX_COLS; c++, col_mask <<= 1) {
            if (matrix_change & ((matrix_row_t)1 << c)) {
                exec_action(r, c, matrix_row);
                dprintf("{.row = %d, .col = %d, .layer = %04X, .pressed = %04X, .time = %u }\n",
                    r, c,
                    (layer_state | default_layer_state),
                    (matrix_row & ((matrix_row_t)1 << c)),
                    timer_read32());

                // record a processed key
                matrix_prev[r] ^= (col_mask);
                // process a key per task call
            }
        }
    }

#ifdef MOUSEKEY_ENABLE
    mousekey_task();
#endif

#ifdef JOYSTICK_ENABLE
    report_mouse_t mouse_report = joystick.handleJoystick();
    // mouse_move(mouse_report.x, mouse_report.y);
#endif
}

KeyboardHost* KeyboardFirmware_::getHost()
{
    return _host;
}

static uint8_t keyboard_leds(void)
{
    return 0;
}

static void send_system(uint16_t data)
{
    KeyboardFirmware.getHost()->sendSystem(data);
}

static void send_keyboard(report_keyboard_t* report_t)
{
    KeyboardReport report(report_t);
    KeyboardFirmware.getHost()->sendKeyboard(report);
}

static void send_mouse(report_mouse_t* report_t)
{
    MouseReport report(report_t);
    KeyboardFirmware.getHost()->sendMouse(report);
    //delete &report;
}

static void send_consumer(uint16_t data)
{
    KeyboardFirmware.getHost()->sendConsumer(data);
}
