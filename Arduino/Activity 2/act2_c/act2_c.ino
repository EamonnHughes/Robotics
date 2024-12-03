#include <PRIZM.h>
PRIZM prizm;

// LISTED AS CHALLENGE IN LOGBOOK
float botWidth = 10.2; 
float botLength = 13.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
  // Set motor inversion
  prizm.setMotorInvert(2, 1);
  // Set servo speed
  prizm.setServoSpeed(1, 35);
}

void loop() {
  while(prizm.readStartButton() == 1) {
    moveInches(24, 180);
    signalRight();
    moveRight(90, 360);
    signalNone();
    moveInches(24, 180);
    signalLeft();
    moveLeft(90, 360);
    signalNone();
    moveInches(24, 180);
    brake();
    blink(3);
    moveInches(-24, -180);
    brake();
    prizm.PrizmEnd();
  }
}

void signalRight() {
  prizm.setServoPosition(1, 0);
}

void signalLeft() {
  prizm.setServoPosition(1, 180);
}

void signalNone() {
  prizm.setServoPosition(1, 90);
}

void blink(int times) {
  for(int j = 0; j < times; j++ ) {
    prizm.setRedLED(1);
    delay(250);
    prizm.setRedLED(0);
    delay(250);
  }
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