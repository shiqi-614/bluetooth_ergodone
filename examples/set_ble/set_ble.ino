#include <SoftwareSerial.h>

#define BAUD_RATE 9600

void setup()
{
    Serial.begin(BAUD_RATE);
    while (!Serial) { }
    Serial1.begin(BAUD_RATE);
    while (!Serial1) { }
    Serial.println("HM-10 set begin");
}

void loop()
{
    if (Serial1.available() > 0) {
        Serial.print(char(Serial1.read()));
    }

    if (Serial.available()) {
        Serial1.write(char(Serial.read()));
    }
}
