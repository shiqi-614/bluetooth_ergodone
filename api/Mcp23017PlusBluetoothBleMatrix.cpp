//
// Created by Cai, Jinsong on 2020/5/16.
//

#include "Mcp23017PlusBluetoothBleMatrix.h"
#include <SoftwareSerial.h>
static uint8_t mcp23017 = 0x20;
static uint8_t row_codes[] = { 0x7F, 0xBF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };

void Mcp23017PlusBluetoothBleMatrix::begin()
{
    dprintf("Mcp23017PlusBluetoothBleMatrix begin\n");

    leftBlebuffIndex = 0;
    leftBleBegin = false;

    Wire.begin();
    Wire.setClock(400000UL); // set I2C to 400khz

    // set group A pins
    Wire.beginTransmission(mcp23017);
    // select register IODIRA
    Wire.write(0x00);
    // set 0b00000000 means all pins are set as output
    Wire.write(0x00);
    Wire.endTransmission();

    // set group B pins
    Wire.beginTransmission(mcp23017);
    // select register IODIRB
    Wire.write(0x01);
    // set 0b11111111 means all pins are set as input
    Wire.write(0xFF);
    Wire.endTransmission();

    // wire pull up resisters to all B pins
    Wire.beginTransmission(mcp23017);
    // select register GPPUB
    Wire.write(0x0D);
    // set 0b11111111 means all pins are pull-up enabled
    Wire.write(0xFF);
    Wire.endTransmission();
    Serial1.begin(BAUD_RATE);
    dprintf("Mcp23017PlusBluetoothBleMatrix begin end\n");
}

void Mcp23017PlusBluetoothBleMatrix::select_row(uint8_t row)
{
    Wire.beginTransmission(mcp23017);
    Wire.write(0x12);
    Wire.write(row_codes[row]);
    Wire.endTransmission();
}

void Mcp23017PlusBluetoothBleMatrix::unselect_rows()
{
    Wire.beginTransmission(mcp23017);
    Wire.write(0x12);
    Wire.write(0xFF);
    Wire.endTransmission();
}

bool Mcp23017PlusBluetoothBleMatrix::isGhostInRow(uint8_t row)
{
    dprintf("is ghost in row %u\n", row);
    return false;
}

matrix_row_t Mcp23017PlusBluetoothBleMatrix::read_cols()
{
    Wire.beginTransmission(mcp23017);
    Wire.write(0x13);
    Wire.endTransmission();
    Wire.requestFrom(mcp23017, (uint8_t)1);
    byte col_data = Wire.read();
    col_data = ~col_data;
    col_data = (col_data >> 1);
    return col_data;
}

Mcp23017PlusBluetoothBleMatrix::Mcp23017PlusBluetoothBleMatrix()
{
    debouncing = DEBOUNCE;
}

bool Mcp23017PlusBluetoothBleMatrix::isOn(uint8_t row, uint8_t col)
{
    return (_matrix[row] & (1 << col));
}

matrix_row_t Mcp23017PlusBluetoothBleMatrix::getRow(uint8_t row)
{
    return _matrix[row];
}

uint8_t Mcp23017PlusBluetoothBleMatrix::scan()
{
    for (uint8_t i = 0; i < RIGHT_HAND_MATRIX_ROWS; i++) {
        select_row(i);
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i + RIGHT_HAND_MATRIX_ROWS] != cols) {
            matrix_debouncing[i + RIGHT_HAND_MATRIX_ROWS] = cols;
            if (debouncing) {
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    //    dprintf("serial ava %d\n", Serial1.available());
    if (Serial1.available()) {
        byte data = Serial1.read();
        dprintf("receive left ble data %04X\n", data);
        if (data == 0xFD) {
            leftBleBegin = true;
            leftBlebuffIndex = 0;
        } else if (leftBleBegin == true) {
            leftBlebuff[leftBlebuffIndex++] = data;
        }
        if (leftBlebuffIndex == 2) {
            leftBlebuffIndex = 0;
            leftBleBegin = false;
            uint8_t row = leftBlebuff[0];
            uint8_t cols = leftBlebuff[1];
            dprintf("receive left ble row %d column: %04X\n", row, cols);
            _matrix[row] = cols;
        }
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            dprintf("debouncing update\n");
            for (uint8_t i = 0; i < RIGHT_HAND_MATRIX_ROWS; i++) {
                _matrix[i + RIGHT_HAND_MATRIX_ROWS] = matrix_debouncing[i + RIGHT_HAND_MATRIX_ROWS];
            }
        }
    }
    return 1;
}

uint8_t Mcp23017PlusBluetoothBleMatrix::getRows()
{
    return MATRIX_ROWS;
}

uint8_t Mcp23017PlusBluetoothBleMatrix::getCols()
{
    return MATRIX_COLS;
}
