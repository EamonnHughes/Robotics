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
int sweep = 500;

void setup() {

  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);
  prizm.setServoSpeed(2, 50);

}

void loop() {
  bool wentLeft = true;

  prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO));

  while(prizm.readSonicSensorCM(2) <= 10) {

    delay(3000);

    while(prizm.readLineSensor(3) == DARK) {
      prizm.setMotorPowers(20, 20);
    }
    brake();

    while(prizm.readSonicSensorCM(2) >= 15) {

      while(prizm.readLineSensor(3) == DARK) {
        if(wentLeft){
          prizm.setMotorPowers(20, -19);
          int time = 0;
          while (prizm.readLineSensor(3) == DARK && time < sweep) {
            if((prizm.readSonicSensorCM(2) < 15)) {
              brake();
              spin(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
            time += 1;
          }
          while (prizm.readLineSensor(3) == DARK) {
            prizm.setMotorPowers(-19, 20);
            if((prizm.readSonicSensorCM(2) < 15)) {
              brake();
              spin(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
          }
          wentLeft = !wentLeft;
        } else {
          prizm.setMotorPowers(-19, 20);
          int time = 0;
          while (prizm.readLineSensor(3) == DARK && time < sweep) {
            if((prizm.readSonicSensorCM(2) < 15)) {
              brake();
              spin(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
            time += 1;
          }
          while (prizm.readLineSensor(3) == DARK) {
            prizm.setMotorPowers(20, -19);
            if((prizm.readSonicSensorCM(2) < 15)) {
              brake();
              spin(90, 360, true);
              prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
              delay(1000);
              prizm.PrizmEnd();
            } 
            delay(1);
          }
          wentLeft = !wentLeft;
        }
        delay(10);
        if((prizm.readSonicSensorCM(2) < 15)) {
          brake();
          spin(90, 360, true);
          prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
          delay(1000);
          prizm.PrizmEnd();
        }
      } 
      delay(10);
      while(prizm.readLineSensor(3) == LIGHT) {
        prizm.setMotorPowers(20, 20);
        if((prizm.readSonicSensorCM(2) < 15)) {
          brake();
          spin(90, 360, true);
          prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
          delay(1000);
          prizm.PrizmEnd();
        }
      }

    }
    brake();
    spin(90, 360, true);
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
  prizm.setMotorPowers(125, 125);
  delay(50);
}

void spin(double degrees, int speed, bool brakeAtEnd) {
  double radians = (abs(degrees) * 2 * PI) / 360;
  double outerWheelInches = radians * BOT_WIDTH; 
  double outerWheelDegrees = (ONE_CIRCLE * outerWheelInches) / (PI * WHEEL_DIAMETER);

  if (((degrees>0)-(degrees<0)) == -1) {
    prizm.setMotorSpeeds(speed/2, -speed/2);
  } else {
    prizm.setMotorSpeeds(-speed/2, speed/2);
  }  
  delay(((outerWheelDegrees / speed) * ONE_SECOND * 1.025));
  if(brakeAtEnd) brake();
}