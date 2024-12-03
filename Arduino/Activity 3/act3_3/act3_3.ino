#include <PRIZM.h>
PRIZM prizm;

float botWidth = 10.2; 
float botLength = 13.0;
float wheelCirc = 4.0;
float oneSecond = 1000.0;
float oneCircle = 360.0;
float signalTime = 200.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();
  // Set motor inversion
  prizm.setMotorInvert(2, 1);
  // Set servo speed
  prizm.setServoSpeed(1, 50);    
}

void loop() {
  moveLeft(90, 360);
  moveRight(90, 360);
  prizm.PrizmEnd();
}

// Signal a right turn
void signalRight() {
  prizm.setServoPosition(1, 90);
  for(int j = 0; j < 3; j++ ) {
    prizm.setRedLED(1);
    delay(100);
    prizm.setRedLED(0);
    delay(100);
  }
}

// Signal a left turn
void signalLeft() {
  prizm.setServoPosition(1, 0);
  for(int j = 0; j < 3; j++ ) {
    prizm.setGreenLED(1);
    delay(100);
    prizm.setGreenLED(0);
    delay(100);
  }
}

void brake() {
  prizm.setMotorPowers(125, 125);
}

// Move X degrees at Y rotations/second
void moveDegrees(float degrees, int speed) {
  prizm.setMotorSpeeds(speed, speed);
  delay(degrees / speed * oneSecond);
}

// Move X rotations at Y rotations/second
void moveRotations(float rotations, int speed) {
  moveDegrees(oneCircle * rotations, speed);
}

// Move X inches at Y rotations/second
void moveInches(float inches, int speed) {
  moveRotations(inches / (PI * wheelCirc), speed);
}

// Move in a X degrees arc rightwards at Y rotations/second of the outer wheel
void moveRight(double degrees, int speed) {
  double outerWheelDegrees = degrees * botWidth;

  prizm.setMotorSpeeds(speed/2, speed);
  signalRight();
  delay((outerWheelDegrees / speed * oneSecond) - signalTime);
}

// Move in a X degrees arc leftwards at Y rotations/second of the outer wheel
void moveLeft(double degrees, int speed) {
  double outerWheelDegrees = degrees * botWidth;

  prizm.setMotorSpeeds(speed, speed/2);
  signalLeft();
  delay((outerWheelDegrees / speed * oneSecond) - signalTime);
}