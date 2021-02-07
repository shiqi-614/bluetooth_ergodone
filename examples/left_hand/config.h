#ifndef KEYBOARDFIRMWARE_CONFIG_H
#define KEYBOARDFIRMWARE_CONFIG_H 1

#define LEFT_HAND 1

#define debug_enable (UDADDR & _BV(ADDEN))

#define MATRIX_ROWS 7
#define MATRIX_COLS 6

#define RX_PIN 3
#define TX_PIN 2

#define DEBOUNCE 5
#define BAUD_RATE 9600

// SDAM -> TX
// SCLM -> RX

#endif
