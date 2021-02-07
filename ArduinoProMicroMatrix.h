#ifndef SPARKFUNPROMICROMATRIX_H
#define SPARKFUNPROMICROMATRIX_H 1

#include "KeyboardMatrix.h"

#define MATRIX_ROWS 7
#define MATRIX_COLS 6
#define DEBOUNCE 5

class ArduinoProMicroMatrix : public KeyboardMatrix {
public:
    ArduinoProMicroMatrix();
    virtual void begin();
    virtual uint8_t scan();
    virtual uint8_t getRows();
    virtual uint8_t getCols();
    virtual bool isOn(uint8_t row, uint8_t col);
    bool isGhostInRow(uint8_t row);
    virtual matrix_row_t getRow(uint8_t row);
    void select_row(uint8_t row);
    matrix_row_t read_cols();
    void unselect_rows(uint8_t row);
    void setLEDs(uint8_t ledStatus);

protected:
    uint8_t _matrix[MATRIX_ROWS];
    matrix_row_t matrix_debouncing[MATRIX_ROWS];
    uint8_t debouncing;
};

#endif
