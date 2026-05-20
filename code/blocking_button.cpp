#include "blocking_button.h"
#include <Arduino.h>

const int buttonPin = 1;

void initButton() {
    pinMode(buttonPin, INPUT);
}

void waitForButton() {
  int buttonState = LOW;
  while (buttonState == LOW) {
    buttonState = digitalRead(buttonPin);
  }
  delay(100);
}