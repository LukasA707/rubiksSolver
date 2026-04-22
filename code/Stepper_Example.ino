#include <Stepper.h>

const int leftReader = 2;
const int rightReader = 3;
const int stepsPerRevolution = 200; // value got from datasheet
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(60);
  pinMode(leftReader, INPUT);
  pinMode(rightReader, INPUT);
}


void stepLeft() {
  myStepper.step(stepsPerRevolution / 4);
}

void stepRight() {
  myStepper.step(-stepsPerRevolution / 4);
}

void loop() {
  delay(100);
  if (1 != digitalRead(leftReader)){
    stepLeft();
  }
  if (1 != digitalRead(rightReader)){
    stepRight();
  }
}

