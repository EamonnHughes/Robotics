 #include <PRIZM.h>
 PRIZM prizm;
 
 int LEVEL_SERVO = -32;
 void setup() {

  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);
  prizm.setServoSpeed(2, 50);

}

void loop() {

  prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO));

  while(prizm.readSonicSensorCM(2) >= 25) {

    if(prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(30, 125);
    }
    if(prizm.readLineSensor(3) == 0) {
      prizm.setMotorPowers(125, 30);
    }

  }
  prizm.setMotorPowers(125, 125);

  while (prizm.readStartButton() == 0) {
    prizm.setGreenLED(HIGH);
    delay(300);
    prizm.setGreenLED(LOW);
    delay(300);
  }

  prizm.setServoPosition(2, getServoAngle(LEVEL_SERVO + 90));
  delay(1000);

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