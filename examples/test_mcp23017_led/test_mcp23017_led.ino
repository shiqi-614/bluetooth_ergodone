#include <Wire.h>

byte mcp23017 = 0x20;
byte row_codes[] = { 0x7F, 0xBF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE };

#define LEDA_PIN 15
#define LEDB_PIN 14
#define LEDC_PIN 16

static uint8_t matrix_prev[7];

void setup() {
    Serial.begin(9600);
    while(!Serial);

    Serial.println("right keyboard matrix with mcp23017 test begin");

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


    pinMode(LEDA_PIN, OUTPUT);
    pinMode(LEDB_PIN, OUTPUT);
    pinMode(LEDC_PIN, OUTPUT);

    digitalWrite(LEDA_PIN, HIGH);
    digitalWrite(LEDB_PIN, HIGH);
    digitalWrite(LEDC_PIN, HIGH);
}

void control_row(byte address, byte val) {
    Wire.beginTransmission(address);
    Wire.write(0x12);
    Wire.write(val);
    Wire.endTransmission();
}

void loop() {
    for (uint8_t row = 0; row < 7; ++row) {
        // select row by sending the corresponding code
        control_row(mcp23017, row_codes[row]);

        Wire.beginTransmission(mcp23017);
        Wire.write(0x13);
        Wire.endTransmission();
        Wire.requestFrom(mcp23017, (uint8_t)1);

        byte col_data = Wire.read();
        col_data = ~col_data;
        if (matrix_prev[row] != col_data) {
            matrix_prev[row] = col_data;
            Serial.print(row);
            Serial.print(' ');
            Serial.println(matrix_prev[row], BIN);
        }
        // release row by setting all pins high
        control_row(mcp23017, 0xFF);
    }
}
