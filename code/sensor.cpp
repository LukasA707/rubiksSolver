#include <Arduino.h>
#include "sensor.h"

Sensor::Sensor(int sensorPin) {
    pin = sensorPin;
    pinMode(sensorPin, INPUT);
}
        
bool Sensor::magnetDetected() {
    return digitalRead(pin) == LOW;
}