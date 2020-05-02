#include <AccelStepper.h>

#define INTERFACE_TYPE 1

#define J1_DIR  4
#define J1_STEP 5
#define J1_ENABLE 6

#define J2_DIR  8
#define J2_STEP 9
#define J2_ENABLE 10

#define BASE_STEPS 200
#define MICRO_STEPS 0.25

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

// Create a new instance of the AccelStepper class:
AccelStepper J1 = AccelStepper(INTERFACE_TYPE, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(INTERFACE_TYPE, J2_STEP, J2_DIR);

int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}

void moveA() {
  J1.move(800);
  J2.move(800);

  while ( (J1.distanceToGo() != 0) || (J2.distanceToGo() != 0) ) {
    J1.run();
    J2.run();
  }

};

void moveB() {
  J1.move(-800);
  J2.move(-800);

  while ( (J1.distanceToGo() != 0) || (J2.distanceToGo() != 0) ) {
    J1.run();
    J2.run();
  }

};

void setup() {
  
  // put your setup code here, to run once:
  J1.setMaxSpeed(800.0);
  J1.setAcceleration(100.0);

  J2.setMaxSpeed(800.0);
  J2.setAcceleration(100.0);
}

void loop() {
  // put your main code here, to run repeatedly:

  moveA();
  moveB();


}
