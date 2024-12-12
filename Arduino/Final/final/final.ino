#include <PRIZM.h>
PRIZM prizm;
 
int LEVEL_SERVO = -32;
double BOT_WIDTH = 10.2; 
double WHEEL_DIAMETER = 4.0;
double ONE_SECOND = 1000.0;
double ONE_CIRCLE = 360.0;
double SIGNAL_TIME = 600.0;
int LIGHT = 0;
int DARK = 1;

void setup() {

  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);
  prizm.setServoSpeed(2, 50);

}

void loop() {
  prizm.setServoPosition(2, 90);
  // This begins the program
  while(prizm.readSonicSensorCM(2) < 15) {
    delay(1000);
    // 
    while(prizm.readSonicSensorCM(2) > 35) {
      prizm.setMotorSpeeds(300, 300);
      while(prizm.readSonicSensorCM(2) > 35) {
        delay(10);
      }
      if(prizm.readSonicSensorCM(2) < 35) {
        brake();
        int newDirection = scanForDirection();
        if(newDirection == 0) {
          spinRight(90, 300, true);
        } else if(newDirection == 1) {
          spinLeft(90, 300, true);
        }
      }
    }
  }

  scanForDirection();

  prizm.PrizmEnd();
}

int scanForDirection() {
  // This function will run when the robot reaches a wall, and tells the robot which way is clear
  // 0 signifies a right turn
  // 1 signifies a left turn
  // If no way is clear, end
  prizm.setServoPosition(2, 0);
  delay(3000);
  if(prizm.readSonicSensorCM(2) >  35) {
    prizm.setServoPosition(2, 90);
    delay(3000);
    return 0;
  }
  prizm.setServoPosition(2, 180);
  delay(3000);
  if(prizm.readSonicSensorCM(2) >  35) {
    prizm.setServoPosition(2, 90);
    delay(3000);
    return 1;
  }
  prizm.PrizmEnd();
}


int getServoAngle(int angle) {
  int newAngle = angle;
  if(newAngle < 0) {
    newAngle += 180;
  }
  newAngle = newAngle % 180;
  return newAngle;
}
void brake() {
  prizm.setMotorSpeeds(0, 0);
  prizm.setMotorPowers(125, 125);
  delay(50);
}

void spinRight(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * BOT_WIDTH; 
  double outerWheelDegrees = (ONE_CIRCLE * outerWheelInches) / (PI * WHEEL_DIAMETER);

  prizm.setMotorSpeeds(-speed/2, speed/2);

  delay(((outerWheelDegrees / speed) * ONE_SECOND * 1.025));
  if(brakeAtEnd) brake();
}

void spinLeft(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * BOT_WIDTH; 
  double outerWheelDegrees = (ONE_CIRCLE * outerWheelInches) / (PI * WHEEL_DIAMETER);
  
  prizm.setMotorSpeeds(speed/2, -speed/2);
  
  delay(((outerWheelDegrees / speed) * ONE_SECOND * 1.025));
  if(brakeAtEnd) brake();
}