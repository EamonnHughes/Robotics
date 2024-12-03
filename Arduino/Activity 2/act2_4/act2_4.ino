#include <PRIZM.h>
PRIZM prizm;

// LISTED AS EXERCISE 5 IN LOGBOOK
float botWidth = 13.5; //middle of wheel to middle of wheel
float botLength = 13.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
  // Set motor inversion
  prizm.setMotorInvert(2, 1);
}

void loop() {
  moveInches(12, 360);
  moveRight(45, 540);
  moveLeft(45, 540);
  moveInches(12, 360);
  brake();
  prizm.PrizmEnd();
}


void moveDegrees(float degrees, int speed) {
  prizm.setMotorSpeeds(speed, speed);
  delay(degrees / speed * 1000);
}

void moveRotations(float rotations, int speed) {
  moveDegrees(360 * rotations, speed);
}

void moveInches(float inches, int speed) {
  moveRotations(inches / (PI * 4.0), speed);
}

void moveRight(double degrees, int speed) {
  double outerWheelDegrees = degrees * botWidth;

  prizm.setMotorSpeeds(speed/2, speed);
  delay(outerWheelDegrees / speed * 1000);
}

void moveLeft(double degrees, int speed) {
  double outerWheelDegrees = degrees * botWidth;

  prizm.setMotorSpeeds(speed, speed/2);
  delay(outerWheelDegrees / speed * 1000);
}

void brake() {
  prizm.setMotorPowers(125, 125);
}