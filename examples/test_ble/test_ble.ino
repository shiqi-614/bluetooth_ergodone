#define BAUD_RATE 9600
#include <SoftwareSerial.h>

void setup() {
    Serial.begin(BAUD_RATE);
    while (!Serial) { }

    Serial1.begin(BAUD_RATE);
    while (!Serial1) { }
   
    Serial.println("HM-10 test begin");
}

void loop() {
    
    if (Serial1.available() > 0) {
        Serial.println(Serial1.read(), HEX);
    }

}
