#include "ArduinoProMicroMatrix.h"
#include "config.h"
#include "gluecode.h"
#include <SoftwareSerial.h>

ArduinoProMicroMatrix matrix;

static matrix_row_t matrix_prev[MATRIX_ROWS];

SoftwareSerial BT(TX_PIN, RX_PIN);

void setup()
{
    matrix.begin();
    BT.begin(BAUD_RATE);
    BT.flush();
    BT.listen();
    print_set_sendchar(arduino_tmk_sendchar);

    if (debug_enable) {
        Serial.begin(9600);
        while (!Serial)
            ;
    }
    dprintf("left hand serial open\n");

    for (int i = 0; i < MATRIX_ROWS; i++) {
        matrix_prev[i] = 0;
    }
}

void loop()
{
    matrix_row_t matrix_row = 0;
    matrix_row_t matrix_change = 0;

    matrix.scan();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        matrix_row = matrix.getRow(r);
        matrix_change = matrix_row ^ matrix_prev[r];
        if (matrix_change) {
            matrix_prev[r] = matrix_row;
            BT.write(0xFD);
            BT.write(r);
            BT.write(matrix_row);

            dprintf("row %d state %04X\n", r, matrix_row);
        }
    }
}
