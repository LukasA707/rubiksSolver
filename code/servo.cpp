#include <Arduino.h>
#include <Servo.h>

Servo pushServo;

const int servoPin = 6;

void initServo() {
    pushServo.attach(servoPin);
}

void servoPush() {
    pushServo.write();
    delay(500);
    pushServo.write(0);   
    delay(50);
}