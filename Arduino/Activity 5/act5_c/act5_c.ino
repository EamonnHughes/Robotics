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
  bool wentRight = false;

  prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO));

  while(prizm.readSonicSensorCM(2) <= 10) {

    delay(3000);

    while(prizm.readSonicSensorCM(2) >= 25) {
      while(prizm.readLineSensor(3) == DARK) {
        if(wentRight){
          while (prizm.readLineSensor(3) == DARK) {
            prizm.setMotorSpeeds(200, 35);
            if((prizm.readSonicSensorCM(2) < 25)) {
              brake();
              spinLeft(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
          }
          delay(100);
          prizm.setMotorSpeeds(100, 100);
          wentRight = false;
        } else {
          while (prizm.readLineSensor(3) == DARK) {
            prizm.setMotorSpeeds(35, 200);
            if((prizm.readSonicSensorCM(2) < 25)) {
              brake();
              spinLeft(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
          }
          delay(100);
          prizm.setMotorSpeeds(100, 100);
          wentRight = true;
        }
        if((prizm.readSonicSensorCM(2) < 25)) {
          brake();
          spinLeft(90, 360, true);
          prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
          delay(1000);
          prizm.PrizmEnd();
        }
      } 
      while(prizm.readLineSensor(3) == LIGHT) {
        prizm.setMotorSpeeds(100, 100);
        if((prizm.readSonicSensorCM(2) < 25)) {
          brake();
          spinLeft(90, 360, true);
          prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
          delay(1000);
          prizm.PrizmEnd();
        }
      }

    }
    brake();
    spinLeft(90, 360, true);
    prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
    delay(1000);
    prizm.PrizmEnd();
      
  }

}


int getServoAngle(int angle) {
  int newAngle = angle;
  if(newAngle < 0) {
    newAngle += 180;
  }
  newAngle = newAngle % 180;
  return newAngle;
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