//
// Created by Cai, Jinsong on 2020/5/16.
// test
//

#include "BluetoothHost.h"
#include "SoftwareSerial.h"

BluetoothHost::BluetoothHost()
{
}

void BluetoothHost::begin()
{

    dprintf("bluetooth host begin\n");
    bluetoothHost = new SoftwareSerial(8, 9);
    bluetoothHost->begin(9600);

    dprintf("bluetooth host begin end\n");
}

void BluetoothHost::sendKeyboard(KeyboardReport& report)
{
    dprintf("keyboard modifiers->%d,0->%d, 1->%d, 2->%d, 3->%d, 4->%d, 5->%d\n",
        report.getModifiers(),
        report.getKey(0),
        report.getKey(1),
        report.getKey(2),
        report.getKey(3),
        report.getKey(4),
        report.getKey(5));

    byte send_buf[] = {
        0x0C, 0x00, 0xA1, 0x01,
        report.getModifiers(),
        0x00,
        report.getKey(0),
        report.getKey(1),
        report.getKey(2),
        report.getKey(3),
        report.getKey(4),
        report.getKey(5)
    };
    bluetoothHost->write(send_buf, 12);
}

void BluetoothHost::sendMouse(MouseReport& report)
{

    dprintf("mouse buttons->%d, X->%d, Y->%d, V->%d, H->%d\n",
        report.getButtons(),
        report.getX(),
        report.getY(),
        report.getV(),
        report.getH());

    byte send_buf[] = {
        0x08, 0x00, 0xA1, 0x02,
        (byte)report.getButtons(),
        (byte)report.getX(),
        (byte)report.getY(),
        (byte)report.getV()
    };
    bluetoothHost->write(send_buf, 8);
};

static uint16_t usage2bits(uint16_t usage)
{
    switch (usage) {
    case APPCONTROL_HOME:
        return 0x01;
    case APPLAUNCH_EMAIL:
        return 0x02;
    case APPCONTROL_SEARCH:
        return 0x04;
        //case AL_KBD_LAYOUT:         return 0x08;  // Apple virtual keybaord toggle
    case AUDIO_MUTE:
        return 0x100;
    case AUDIO_VOL_DOWN:
        return 0x200;
    case AUDIO_VOL_UP:
        return 0x400;
    case TRANSPORT_PLAY_PAUSE:
        return 0x800;
    case TRANSPORT_STOP:
        return 0x1000;
    case TRANSPORT_PREV_TRACK:
        return 0x2000;
    case TRANSPORT_NEXT_TRACK:
        return 0x4000;
        //case TRANSPORT_STOP_EJECT:    return 0x800;
        //case TRANSPORT_FAST_FORWARD:  return 0x1000;
        //case TRANSPORT_REWIND:        return 0x2000;
        //case return 0x4000;   // Stop/eject
        //case return 0x8000;   // Internet browser
    };
    return 0;
}
void BluetoothHost::sendConsumer(uint16_t data)
{
    uint16_t bits = usage2bits(data);
    dprintf("send consusmer: %04X\n", bits);
    byte send_buf[] = { 0x08, 0x00, 0xA1, 0x03, (byte)(bits & 0xFF), (byte)((bits >> 8) & 0xFF), 0x00, 0x00 };
    bluetoothHost->write(send_buf, 8);
};

void BluetoothHost::sendSystem(uint16_t data)
{
    // not implemented
    dprintf("send system: %04X\n", data);
}
