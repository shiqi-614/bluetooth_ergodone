#ifndef KEYBOARDREPORT_H
#define KEYBOARDREPORT_H

#include "KeyboardFirmware.h"
#include "tmk/tmk_keyboard/tmk_core/common/report.h"

class KeyboardReport {
public:
    KeyboardReport(report_keyboard_t* report);
    uint8_t getModifiers();
    uint8_t getReserved();
    uint8_t getReportKeys();
    uint8_t getKey(uint8_t keyIndex);

private:
    report_keyboard_t* _report;
};

#endif
