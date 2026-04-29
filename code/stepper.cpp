#include "stepper.h"

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void initStepper() {
  myStepper.setSpeed(60);
}

void stepLeft() {
  myStepper.step(stepsPerRevolution / 4);
}

void stepRight() {
  myStepper.step(-stepsPerRevolution / 4);
}

void stepHalfRevolution() {
  myStepper.step(stepsPerRevolution / 2);
}