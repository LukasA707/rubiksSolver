#define STEPPER_CONTROL_H

#include <Stepper.h>

extern const int leftReader;
extern const int rightReader;
extern const int stepsPerRevolution;
extern Stepper myStepper;

void stepLeft();
void stepRight();