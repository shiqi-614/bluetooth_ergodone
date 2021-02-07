#ifndef MCP23017PLUSBLUETOOTHBLEMATRI_H
#define MCP23017PLUSBLUETOOTHBLEMATRI_H 1

#include "KeyboardFirmware.h"
#include <SoftwareSerial.h>
#include <Wire.h>

class Mcp23017PlusBluetoothBleMatrix : public KeyboardMatrix {
public:
    Mcp23017PlusBluetoothBleMatrix();
    virtual void begin();
    virtual uint8_t scan();
    virtual uint8_t getRows();
    virtual uint8_t getCols();
    virtual bool isOn(uint8_t row, uint8_t col);
    virtual matrix_row_t getRow(uint8_t row);
    virtual bool isGhostInRow(uint8_t row);
    void select_row(uint8_t row);
    matrix_row_t read_cols();
    void unselect_rows();

protected:
    uint8_t _matrix[MATRIX_ROWS];
    uint8_t leftBlebuff[10];
    uint8_t leftBlebuffIndex;
    bool leftBleBegin;
    matrix_row_t matrix_debouncing[MATRIX_ROWS];
    uint8_t debouncing;
};

#endif
