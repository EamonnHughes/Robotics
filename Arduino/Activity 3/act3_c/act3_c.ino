#include <PRIZM.h>
PRIZM prizm;

double botWidth = 10.2; 
double botLength = 13.0;
double wheelDiameter = 4.0;
double oneSecond = 1000.0;
double oneCircle = 360.0;
double signalTime = 600.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();
  // Set motor inversion
  prizm.setMotorInvert(2, 1);
  // Set servo speed
  prizm.setServoSpeed(1, 50);    
}

void loop() {
  doCourse();
  prizm.PrizmEnd();
}

// Instructions to navigate the course
void doCourse() {
  moveInches(6, 360, true);
  turnLeft(90, 360, true);
  moveInches(15, 360, true);
  turnLeft(45, 360, true);
  moveInches(3.75, 360, true);
  turnRight(45, 360, true);
  moveInches(18, 360, true);
  spin(180, 360, true);
  moveInches(12, 360, true);
  turnLeft(90, 360, true);
  moveInches(26, 360, true);
  turnRight(90, 360, true);
  moveInches(17, 360, true);
  turnLeft(90, 360, true);
  moveInches(18, 360, true);
  spin(180, 360, true);
  moveInches(12, 360, true);
  turnRight(90, 360, true);
  moveInches(24, 360, true);
  turnRight(90, 360, true);
  moveInches(3.5, 360, true);
  turnLeft(90, 360, true);
  moveInches(18, 360, true);

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
  delay(50);
}

// Move X degrees at Y degrees/second
void moveDegrees(double degrees, int speed, bool brakeAtEnd) {
  if (((degrees>0)-(degrees<0)) == -1) {
    prizm.setMotorSpeeds(-speed, -speed);
  } else {
    prizm.setMotorSpeeds(speed, speed);
  }
  double realDegrees = abs(degrees);
  delay(realDegrees / speed * oneSecond);
  if(brakeAtEnd) brake();
}

// Move X rotations at Y degrees/second
void moveRotations(double rotations, int speed, bool brakeAtEnd) {
  moveDegrees(oneCircle * rotations, speed, brakeAtEnd);
}

// Move X inches at Y degrees/second
void moveInches(double inches, int speed, bool brakeAtEnd) {
  moveRotations(inches / (PI * wheelDiameter), speed, brakeAtEnd);
}

// Move in a X degrees arc rightwards at Y degrees/second of the outer wheel
void turnRight(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * botWidth; 
  double outerWheelDegrees = (oneCircle * outerWheelInches) / (PI * wheelDiameter);

  signalRight();
  if (((degrees>0)-(degrees<0)) == -1) {
    prizm.setMotorSpeeds(0, -speed);
  } else {
    prizm.setMotorSpeeds(0, speed);
  }
  delay(((outerWheelDegrees / speed) * oneSecond));
  if(brakeAtEnd) brake();
}

// Move in a X degrees arc leftwards at Y degrees/second of the outer wheel
void turnLeft(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * botWidth; 
  double outerWheelDegrees = (oneCircle * outerWheelInches) / (PI * wheelDiameter);

  signalLeft();
  if (((degrees>0)-(degrees<0)) == -1) {
    prizm.setMotorSpeeds(-speed, 0);
  } else {
    prizm.setMotorSpeeds(speed, 0);
  }  
  delay(((outerWheelDegrees / speed) * oneSecond));
  if(brakeAtEnd) brake();
}
void spin(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * botWidth; 
  double outerWheelDegrees = (oneCircle * outerWheelInches) / (PI * wheelDiameter);

  if (((degrees>0)-(degrees<0)) == -1) {
    prizm.setMotorSpeeds(speed/2, -speed/2);
  } else {
    prizm.setMotorSpeeds(-speed/2, speed/2);
  }  
  delay(((outerWheelDegrees / speed) * oneSecond * 1.025));
  if(brakeAtEnd) brake();
}