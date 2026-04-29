#include <Arduino.h>

const int solenoidPin = 12;

void initSolenoid() {
    pinMode(solenoidPin, OUTPUT);
}

void solenoidPush() {
    digitalWrite(solenoidPin, 1);
    delay(500);
    digitalWrite(solenoidPin, 0);   
    delay(50);
}