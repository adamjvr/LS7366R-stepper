#include "ls7366r_arduino.h"
#include <AccelStepper.h>

// LS7366R and SPI configuration
#define LS7366R_CS_PIN 10
#define LS7366R_SPI_PORT SPI

// Stepper motor connections
#define STEPPER_DIR_PIN 2    // Direction pin for stepper motor driver
#define STEPPER_STEP_PIN 3   // Step pin for stepper motor driver
#define STEPPER_ENABLE_PIN 4 // Enable pin for stepper motor driver

// Number of rotations to perform
const float targetRotations = 2.0;

// Define LS7366R object
LS7366R encoder(LS7366R_CS_PIN, LS7366R_SPI_PORT);

// Define AccelStepper object
AccelStepper stepper(AccelStepper::DRIVER, STEPPER_STEP_PIN, STEPPER_DIR_PIN);

// Function to drive the stepper motor a specified number of rotations
void driveStepperRotations(float rotations);

void setup() {
  Serial.begin(9600);

  // Initialize LS7366R and AccelStepper
  encoder.init();
  stepper.setMaxSpeed(2000.0);    // Set your desired max speed (steps per second)
  stepper.setAcceleration(1000.0); // Set your desired acceleration (steps per second^2)

  // Enable the stepper motor driver
  pinMode(STEPPER_ENABLE_PIN, OUTPUT);
  digitalWrite(STEPPER_ENABLE_PIN, LOW);

  // Move the stepper motor to the initial position
  stepper.setCurrentPosition(0);
  stepper.moveTo(0);
}

void loop() {
  // Call the function to drive the stepper motor a specified number of rotations
  driveStepperRotations(targetRotations);

  // Stop the program after completing the rotations
  while (1) {
    // Do nothing
  }
}

// Function to drive the stepper motor a specified number of rotations
void driveStepperRotations(float rotations) {
  // Check if the target rotations are reached
  if (stepper.distanceToGo() == 0) {
    Serial.println("Target rotations reached!");
    return;
  }

  // Read the LS7366R counter value and convert it to rotations
  uint32_t counterValue = encoder.readCounter();
  float currentRotations = counterValue / 200.0; // Assuming 200 steps per revolution

  // Print current rotations
  Serial.print("Current Rotations: ");
  Serial.println(currentRotations);

  // Calculate the remaining rotations to the target
  float remainingRotations = rotations - currentRotations;

  // Convert remaining rotations to steps
  long remainingSteps = remainingRotations * 200.0; // Assuming 200 steps per revolution

  // Move the stepper motor to the target position
  stepper.moveTo(remainingSteps);

  // Update the AccelStepper object
  stepper.run();
}
