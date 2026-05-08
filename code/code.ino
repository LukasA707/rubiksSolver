#include "stepper.h"
#include "servo.h"

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
  //initSolenoid();
  initServo();
  Serial.println("Ready for commands");
}

void loop() {
  // For the first MVP we could add a blocker here, that blocks until some button is pressed, in case we need manual intervention?
  delay(100);

  while (Serial.available() == 0) {}

  String command = Serial.readString();

  switch(parseCommand(command)) {
    // TODO: What is left / right in this context?
    case CMD_SPIN_CW:
      executeCommand(command, stepRight);
      break;
    case CMD_SPIN_CCW:
      executeCommand(command, stepLeft);
      break;
    case CMD_SPIN_FULL:
      executeCommand(command, stepHalfRevolution);
    case CMD_TURN_CW:
    case CMD_TURN_CCW:
    case CMD_TURN_FULL:
      Serial.println("Command not implemented: " + command);
      break;
    case CMD_FLIP:    
      executeCommand(command, servoPush);
      break;  
    case CMD_NONE:
    default:
      Serial.println("Invalid command: " + command);
      break;
  }
}