#ifndef KEYBOARDFIRMWARE_CONFIG_H
#define KEYBOARDFIRMWARE_CONFIG_H 1

#define debug_enable (UDADDR & _BV(ADDEN))
#define BAUD_RATE 9600

#define RIGHT_HAND 1

#define EXTRAKEY_ENABLE 1
#define MOUSEKEY_ENABLE 1
#define JOYSTICK_ENABLE 1

#define MATRIX_ROWS 14
#define MATRIX_COLS 6

#define RIGHT_HAND_MATRIX_ROWS 7
#define RIGHT_HAND_MATRIX_COLS 6

#define BLUETOOTH_HOST_RX_PIN 8
#define BLUETOOTH_HOST_TX_PIN 9

// SDAM -> arduino pro micro 2 pin
// SCLM -> arduino pro micro 3 pin
// BLE RX -> arudino pro micro TX
// BLE TX -> arudino pro micro RX
// HC03 RX -> pin 9
// HC03 TX -> pin 8

#define JOYSTICK_X_PIN A3
#define JOYSTICK_Y_PIN A2
#define JOYSTICK_BUTTON_PIN A1

//double unit = ((value * MOUSEKEY_MAX_SPEED) / JOYSTICK_MOUSE_SENSITIVITY) / JOYSTICK_2_MOUSE_RATIO;
//for (int i = 0; i < joystick_repeat; i++)
//  unit *= JONYSTICK_MOVE_EXPONENTIAL_BASE;

// the range of value read from joystick pin
#define JOYSTICK_MOUSE_SENSITIVITY 32
#define JOYSTICK_2_MOUSE_RATIO 4

#define JONYSTICK_MOVE_EXPONENTIAL_BASE 1.03

// if this value is too small, your mouse maybe move your control.
#define JONYSTICK_MOUSE_MOVE_THRESHOLD 4

#define LEDA_PIN 15
#define LEDB_PIN 14
#define LEDC_PIN 16

#define DEBOUNCE 5

#define MOUSEKEY_ENABLE 1
#define MOUSEKEY_MAX_SPEED 30
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MOVE_MAX 20

#endif
