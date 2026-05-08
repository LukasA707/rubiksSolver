#include "stepper.h"

const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void initStepper() {
  myStepper.setSpeed(60);
}

void stepperStep(int deg) {
  // TODO: What happens if we try to step less than 1 (i.e. if we ask it to step 1 degree)
  // We might want to do that if we have to do micro-adjustments
  // If it breaks, the simplest solution might just be to take min here, so it steps at least 1 step no matter what is asked
  myStepper.step(stepsPerRevolution / (360 / deg))
}
