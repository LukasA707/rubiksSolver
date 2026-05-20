#include "stepper.h"
#include "servo.h"
#include "sensor.h"

// Define command API available to algorithm 
// Note that clockwise means from the perspective of the bottom face,
// i.e. the opposite of what you would expect if you sit facing the front face of the cube
enum Command {
  CMD_NONE,
  CMD_SPIN_CW,    // Spins entire cube 90 deg clockwise
  CMD_SPIN_CCW,   // Spins entire cube 90 deg counter-clockwise
  CMD_SPIN_FULL,  // Spins entire cube 180 deg
  CMD_TURN_CW,    // Turn bottom layer 90 deg clockwise
  CMD_TURN_CCW,   // Turns bottom layer 90 deg counter-clockwise
  CMD_TURN_FULL,  // Turns bottom layer 180 deg
  CMD_FLIP        // Flip cube (front face becomes bottom face)
};

// Convert String to enum
Command parseCommand(String cmd) {
  cmd.trim();

  if (cmd == "spin_cw_half") return CMD_SPIN_CW;    
  if (cmd == "spin_ccw_half") return CMD_SPIN_CCW;  
  if (cmd == "spin_full") return CMD_SPIN_FULL;     
  if (cmd == "turn_cw_half") return CMD_TURN_CW;    
  if (cmd == "turn_ccw__half") return CMD_TURN_CCW; 
  if (cmd == "turn_full") return CMD_TURN_FULL;     
  if (cmd == "flip") return CMD_FLIP;               

  return CMD_NONE;
}

void executeCommand(String command, void (*f)()) {
  f();
  command.trim();
  Serial.println(command + "_ok");
}

void setup() {
  Serial.begin(9600);
  initStepper();
  // TODO: Correct pins for sensors and note which belong where
  Sensor s0 = Sensor(5);
  Sensor s1 = Sensor(6);
  Sensor s2 = Sensor(7);
  Sensor s3 = Sensor(8);
  //initSolenoid();
  initServo();
  Serial.println("Ready for commands");
}

void loop() {
  delay(100);

  while (Serial.available() == 0) {}

  String command = Serial.readString();

  switch(parseCommand(command)) {
    case CMD_SPIN_CW:
      executeCommand(command, spin_cw);
      break;
    case CMD_SPIN_CCW:
      executeCommand(command, spin_ccw);
      break;
    case CMD_SPIN_FULL:
      executeCommand(command, spin_full);
      break;
    case CMD_TURN_CW:
      executeCommand(command, turn_cw);
      break;
    case CMD_TURN_CCW:
      executeCommand(command, turn_ccw);
      break;
    case CMD_TURN_FULL:
      executeCommand(command, turn_full);
      break;
    case CMD_FLIP:    
      executeCommand(command, flip);
      break;  
    case CMD_NONE:
    default:
      Serial.println("Invalid command: " + command);
      break;
  }
}

// We should do adjustments in these functions if our sensors indicate that the spin / turn / flip was not successful
// For an MVP, we could also just block until some button is pressed (if sensors indicate error?), to allow for manual intervention 
void spin_cw() {
  stepperStep(90);
}
void spin_ccw() {
  stepperStep(-90);
}
void spin_full() {
  stepperStep(180);
}
// TODO: Clamp cube before stepping in all the turn functions
void turn_cw() {
  stepperStep(90);
}
void turn_ccw() {
  stepperStep(-90);
}
void turn_full() {
  stepperStep(180);
}
void flip() {
  servoPush();
}