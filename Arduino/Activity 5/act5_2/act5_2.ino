 #include <PRIZM.h>
 PRIZM prizm;
 
 void setup() {

  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);

}

void loop() {

  while(prizm.readSonicSensorCM(2) >= 25) {

    if(prizm.readLineSensor(3) == 1) {
      prizm.setMotorPowers(30, 125);
    }
    if(prizm.readLineSensor(3) == 0) {
      prizm.setMotorPowers(125, 30);
    }

  }
  prizm.setMotorPowers(125, 125);

}
