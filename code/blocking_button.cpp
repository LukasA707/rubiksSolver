#include "blocking_button.h"
#include <Arduino.h>

// Button we can add, s.t. we can block progress in the solver until we press this button (for manual intervention)
// Maybe we should also add an led that indicates we are waiting for button press?
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