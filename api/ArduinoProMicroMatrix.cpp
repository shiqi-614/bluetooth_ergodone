#include "ArduinoProMicroMatrix.h"
#include <SoftwareSerial.h>

static int8_t row_pins[] = { 8, 7, 6, 5, 4, 0, 1 };
static int8_t col_pins[] = { A3, A2, A1, A0, 15, 16 };

ArduinoProMicroMatrix::ArduinoProMicroMatrix()
{
}

void ArduinoProMicroMatrix::begin()
{
    for (int8_t pin : row_pins) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }
    for (int8_t pin : col_pins) {
        pinMode(pin, INPUT_PULLUP);
    }
    debouncing = DEBOUNCE;
}

void ArduinoProMicroMatrix::select_row(uint8_t row)
{
    digitalWrite(row_pins[row], LOW);
}

void ArduinoProMicroMatrix::unselect_rows(uint8_t row)
{
    digitalWrite(row_pins[row], HIGH);
}

matrix_row_t ArduinoProMicroMatrix::read_cols()
{
    matrix_row_t state = 0;
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        if (digitalRead(col_pins[i]) == LOW) {
            state |= (1 << i);
        }
    }
    return state;
}

bool ArduinoProMicroMatrix::isOn(uint8_t row, uint8_t col)
{
    return (_matrix[row] & (1 << col));
}

matrix_row_t ArduinoProMicroMatrix::getRow(uint8_t row)
{
    return _matrix[row];
}

uint8_t ArduinoProMicroMatrix::scan()
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            debouncing = DEBOUNCE;
        }
        unselect_rows(i);
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                _matrix[i] = matrix_debouncing[i];
            }
        }
    }
    return 1;
}

bool ArduinoProMicroMatrix::isGhostInRow(uint8_t row)
{
    return false;
}

uint8_t ArduinoProMicroMatrix::getRows()
{
    return MATRIX_ROWS;
}

uint8_t ArduinoProMicroMatrix::getCols()
{
    return MATRIX_COLS;
}
