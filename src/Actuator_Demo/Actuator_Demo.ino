#include "actuator.h"

// Define LS7366R and SPI configuration
#define LS7366R_CS_PIN 10
#define LS7366R_SPI_PORT SPI

// Define Stepper motor connections
#define STEPPER_STEP_PIN 2    // Change this to the actual pin connected to the stepper motor driver step input
#define STEPPER_DIR_PIN 3     // Change this to the actual pin connected to the stepper motor driver direction input
#define STEPPER_ENABLE_PIN 4  // Change this to the actual pin connected to the stepper motor driver enable input
#define LIMIT_SWITCH_PIN 5    // Change this to the actual pin connected to the limit switch

// Create an Actuator object
Actuator actuator(LS7366R_CS_PIN, LS7366R_SPI_PORT, STEPPER_STEP_PIN, STEPPER_DIR_PIN, LIMIT_SWITCH_PIN);

void setup() {
  Serial.begin(9600);

  // Initialize Actuator
  actuator.init();
}

void loop() {
  // Drive the stepper motor clockwise for 2 rotations
  Serial.println("Driving clockwise for 2 rotations...");
  actuator.driveClockwiseRotations(2.0);
  delay(2000);  // Wait for 2 seconds

  // Drive the stepper motor counterclockwise for 1 rotation
  Serial.println("Driving counterclockwise for 1 rotation...");
  actuator.driveCounterclockwiseRotations(1.0);
  delay(2000);  // Wait for 2 seconds

  // Home the actuator counterclockwise until the limit switch is triggered
  Serial.println("Homing counterclockwise...");
  actuator.homeActuator(1);
  delay(2000);  // Wait for 2 seconds

  // Home the actuator clockwise until the limit switch is triggered
  Serial.println("Homing clockwise...");
  actuator.homeActuator(0);
  delay(2000);  // Wait for 2 seconds
}
