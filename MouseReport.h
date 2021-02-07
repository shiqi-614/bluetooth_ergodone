#ifndef MOUSEREPORT_H
#define MOUSEREPORT_H

#include "KeyboardFirmware.h"
#include "tmk/tmk_keyboard/tmk_core/common/report.h"

class MouseReport {
public:
    MouseReport(report_mouse_t* report);
    int8_t getButtons();
    int8_t getX();
    int8_t getY();
    int8_t getV();
    int8_t getH();

private:
    report_mouse_t* _report;
};

#endif
