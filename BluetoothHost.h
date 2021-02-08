#ifndef ESP32HOST_H
#define ESP32HOST_H 1

#include "KeyboardFirmware.h"
#include <SoftwareSerial.h>

class BluetoothHost : public KeyboardHost {
public:
    BluetoothHost();
    virtual void begin();
    virtual void sendKeyboard(KeyboardReport& report);
    virtual void sendMouse(MouseReport& report);
    virtual void sendConsumer(uint16_t data);
    virtual void sendSystem(uint16_t data);

protected:
    void _serial_send(uint8_t data);

private:
    SoftwareSerial* bluetoothHost;
};

#endif
