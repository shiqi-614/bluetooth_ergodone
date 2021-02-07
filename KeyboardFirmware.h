#ifndef KEYBOARDFIRMWARE_H
#define KEYBOARDFIRMWARE_H 1

#include "Arduino.h"
#include "KeyboardHost.h"
#include "KeyboardKey.h"
#include "KeyboardMatrix.h"
#include "KeyboardReport.h"
#include "MouseReport.h"
#include "gluecode.h"
#include <SoftwareSerial.h>

#ifdef RIGHT_HAND
#include "BluetoothHost.h"
#include "Joystick.h"
#include "Mcp23017PlusBluetoothBleMatrix.h"
#endif

#ifdef LEFT_HAND
#include "ArduinoProMicroMatrix.h"
#endif

class KeyboardFirmware_ {
public:
    KeyboardFirmware_();
    void runTask(void);
    void begin(KeyboardHost& host, KeyboardMatrix& matrix);
    void setLEDs(uint8_t leds);
    KeyboardHost* getHost();
    KeyboardMatrix* getMatrix();

private:
    uint8_t led_status;
    KeyboardHost* _host;
    KeyboardMatrix* _matrix;
#ifdef RIGHT_HAND
    Joystick joystick;
#endif
    matrix_row_t matrix_prev[MATRIX_ROWS];
};

extern KeyboardFirmware_ KeyboardFirmware;

#endif
