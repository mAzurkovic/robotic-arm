#include <AccelStepper.h>

#define RATIO 28.44

#define BASE_STEPS 200
#define MICRO_STEPS 0.25

AccelStepper J1 = AccelStepper(1, 5, 4);
AccelStepper J2 = AccelStepper(1, 9, 8);

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

int angleToSteps(float angle) {
  return (int) (RATIO * angle / degreesPerStep);
}


void moveJoints(AccelStepper joint1, AccelStepper joint2, float * jointAngles, int acceleration) {  
  int stepsJ1 = angleToSteps(jointAngles[0]);
  int stepsJ2 = angleToSteps(jointAngles[1]);

  joint1.setAcceleration(acceleration);
  joint2.setAcceleration(acceleration);

  
  joint1.move(stepsJ1);
  joint2.move(stepsJ2);  

   while ( 
    (joint1.distanceToGo() != 0) || 
    (joint2.distanceToGo() != 0) 
    ) {
      joint1.run();
      joint2.run();
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
  J1.setSpeed(800);
  J1.setAcceleration(400.0);

  J2.setMaxSpeed(800);
  J2.setSpeed(800);
  J2.setAcceleration(400.0);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  //moveJoint(J2, angleToSteps(190), 1600);
  //moveJoint(J2, angleToSteps(-190), 1600);

  float jointAngles[] = {45.0, 45.0, 0, 0}; 
  float jointAngles2[] = {-45.0, -45.0, 0, 0}; 

  moveJoints(J1, J2, jointAngles, 1600);
  moveJoints(J1, J2, jointAngles2, 1600);

  delay(500);
}
