#include "../MouseReport.h"

MouseReport::MouseReport(report_mouse_t* report)
{
    this->_report = report;
}

int8_t MouseReport::getButtons()
{
    return this->_report->buttons;
}

int8_t MouseReport::getX()
{
    return this->_report->x;
}

int8_t MouseReport::getY()
{
    return this->_report->y;
}

int8_t MouseReport::getV()
{
    return this->_report->v;
}

int8_t MouseReport::getH()
{
    return this->_report->h;
}
