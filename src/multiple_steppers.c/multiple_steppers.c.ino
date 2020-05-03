#include <AccelStepper.h>
#include "inverse_kinematics.h"

#define BASE_STEPS 200
#define MICRO_STEPS 0.25

#define INTERFACE_TYPE 1

#define J1_DIR  4
#define J1_STEP 5
#define J1_ENABLE 6

#define J2_DIR  8
#define J2_STEP 9
#define J2_ENABLE 10

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

float jointAngles[4];

AccelStepper J1 = AccelStepper(INTERFACE_TYPE, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(INTERFACE_TYPE, J2_STEP, J2_DIR);

int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}


void moveJoints(int angleJ1, int angleJ2) {
  J1.move( angleToSteps(angleJ1) );
  J2.move( angleToSteps(angleJ2) );  

   while ( 
    (J1.distanceToGo() != 0) || 
    (J2.distanceToGo() != 0) 
    ) {
      J1.run();
      J2.run();
  }
}

void setup() {
    
  Serial.begin(9600);

  //----------------------------------------------------------------
  //  Setting speed and acceleration parameters for each joint
  //----------------------------------------------------------------
  J1.setMaxSpeed(800.0);
  J1.setAcceleration(400.0);

  J2.setMaxSpeed(800.0);
  J2.setAcceleration(400.0);

  delay(500);

}

void loop() {


  float pos[] = {0.11496, 0.0, 0.09877};
  inverseKinematics(0, pos, jointAngles);
  moveJoints(jointAngles[1], jointAngles[2]);

  delay(10000);

  /*delay(500);
  moveJoints(-180, 360);
  delay(500);
  moveJoints(180, -360);
  delay(25); */


}
