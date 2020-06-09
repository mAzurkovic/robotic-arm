#include <AccelStepper.h>

#define RATIO 28.44

#define BASE_STEPS 200
#define MICRO_STEPS 0.25

#define J1_DIR  4
#define J1_STEP 5

#define J2_DIR  8
#define J2_STEP 9

#define J3_DIR  11
#define J3_STEP 12

AccelStepper J1 = AccelStepper(1, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(1, J2_STEP, J2_DIR);
AccelStepper J3 = AccelStepper(1, J3_STEP, J3_DIR);


const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

int angleToSteps(float angle) {
  return (int) (RATIO * angle / degreesPerStep);
}


void moveJoints(AccelStepper joint1, 
                AccelStepper joint2, 
                AccelStepper joint3,
                float * jointAngles, 
                int acceleration) {  
                  
  int stepsJ1 = angleToSteps(jointAngles[0]);
  int stepsJ2 = angleToSteps(jointAngles[1]);
  int stepsJ3 = angleToSteps(jointAngles[2]);


  joint1.setAcceleration(acceleration);
  joint2.setAcceleration(acceleration);
  joint3.setAcceleration(acceleration);
  
  joint1.move(stepsJ1);
  joint2.move(stepsJ2);
  joint3.move(stepsJ3);  


   while ( 
    (joint1.distanceToGo() != 0) || 
    (joint2.distanceToGo() != 0) ||
    (joint3.distanceToGo() != 0) 
    ) {
      joint1.run();
      joint2.run();
      joint3.run();

  }
} 


void moveJoint(AccelStepper joint1, float stepsJ1, int acceleration) {  
  joint1.setAcceleration(acceleration);
  
  joint1.move(stepsJ1);

   while ( (joint1.distanceToGo() != 0) ) {
      joint1.run();
  }
} 

void setup() {
  // put your setup code here, to run once:
  J1.setMaxSpeed(800);
  J1.setAcceleration(400.0);

  J2.setMaxSpeed(800);
  J2.setAcceleration(400.0);

  J3.setMaxSpeed(800);
  J3.setAcceleration(400.0);

}

void loop() {
  
  // put your main code here, to run repeatedly:

  float jointAngles[] = {45.0, 45, 30, 0}; 
  float jointAngles2[] = {-45.0, -45, -30, 0}; 

  moveJoints(J1, J2, J3, jointAngles, 1600);
  moveJoints(J1, J2, J3, jointAngles2, 1600);

  delay(500);
}
