#include "stepper.h"
#include "servo.h"

// Define command types
enum Command {
  CMD_NONE,
  CMD_LEFT,
  CMD_RIGHT,
  CMD_PUSH,
  CMD_HALF
};

// Convert String to enum
Command parseCommand(String cmd) {
  cmd.trim();

  if (cmd == "left") return CMD_LEFT;
  if (cmd == "right") return CMD_RIGHT;
  if (cmd == "push") return CMD_PUSH;
  if (cmd == "half") return CMD_HALF;

  // COMMANDS NEEDED BY ALGORITHM (API)
  // Note that clockwise means from the perspective of the bottom face,
  // i.e. the opposite of what you would expect if you sit facing the front face of the cube
  // if (cmd == "spin_cw_half") // Spins entire cube 90 deg clockwise
  // if (cmd == "spin_ccw_half") // Spins entire cube 90 deg counter-clockwise
  // if (cmd == "spin_full") // Spins entire cube 180 deg
  // if (cmd == "turn_cw_half") // Turn bottom layer 90 deg clockwise
  // if (cmd == "turn_ccw__half") // Turns bottom layer 90 deg counter-clockwise
  // if (cmd == "turn_full") // Turns bottom layer 180 deg
  // if (cmd == "flip") // Flip cube (front face becomes bottom face)

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
  delay(100);

  while (Serial.available() == 0) {}

  String command = Serial.readString();

  switch(parseCommand(command)) {
    case CMD_RIGHT:
      executeCommand(command, stepRight);
      break;
    case CMD_LEFT:
      executeCommand(command, stepLeft);
      break;

    case CMD_HALF:
      executeCommand(command, stepHalfRevolution);
      break;

    case CMD_PUSH:
      executeCommand(command, servoPush);
      break;

    case CMD_NONE:
    default:
      Serial.println("Invalid command: " + command);
      break;
  }
}