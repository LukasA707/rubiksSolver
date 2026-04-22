#include "stepper_control.h"

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

  return CMD_NONE;
}

void executeCommand(String command, void (*f)()) {
  f();
  command.trim();
  Serial.println(command + ": ok");
}

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(60);
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
      break;

    case CMD_NONE:
    default:
      Serial.println("Invalid command: " + command);
      break;
  }
}