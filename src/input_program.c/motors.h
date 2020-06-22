#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

#define BASE_STEPS 200
#define MICRO_STEPS 0.25
#define MAX_SPS 800
#define JOINT_SPACE 4

#define LARGE_RATIO 28.44
#define SMALL_RATIO 18.78

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;


// Helper function to convert to steps
int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}

int findMaximum(float a[], int n) {
  int c, maximum, index;
  maximum = a[0];
  index = 0;
 
  for (c = 1; c < n; c++) {
    if (a[c] > maximum) {
       index = c;
       maximum = a[c];
    }
  }
  return index;
}

void moveJoints(AccelStepper joint1, AccelStepper joint2, AccelStepper joint3, float * jointAngles, int acceleration) {  
  int stepsJ1 = -1 * angleToSteps(jointAngles[0]) * LARGE_RATIO;
  int stepsJ2 = -1 * angleToSteps(jointAngles[1]) * LARGE_RATIO;
  int stepsJ3 = 0 ? (jointAngles[2] == 0) : (-1 * angleToSteps(jointAngles[2]) * SMALL_RATIO);


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

void interpolatedRun(AccelStepper joint1, AccelStepper joint2, AccelStepper joint3, AccelStepper joint4, float * jointAngles, int acceleration) {  
  float jointTimes[JOINT_SPACE];
  int maxIndex;
  
  float stepsJ1 = -1 * angleToSteps(jointAngles[0]) * LARGE_RATIO;
  float stepsJ2 = -1 * angleToSteps(jointAngles[1]) * LARGE_RATIO;
  float stepsJ3 = (-1 * angleToSteps(jointAngles[2]) * LARGE_RATIO);
  float stepsJ4 = (-1 * angleToSteps(jointAngles[3]) * SMALL_RATIO);

  jointTimes[0] = abs(stepsJ1 / MAX_SPS);
  jointTimes[1] = abs(stepsJ2 / MAX_SPS);
  jointTimes[2] = abs(stepsJ3 / MAX_SPS);
  jointTimes[3] = abs(stepsJ4 / MAX_SPS);

  joint1.setAcceleration(acceleration);
  joint2.setAcceleration(acceleration);
  joint3.setAcceleration(acceleration);
  joint4.setAcceleration(acceleration);

  maxIndex = findMaximum(jointTimes, JOINT_SPACE); 

  Serial.println(jointTimes[maxIndex]); 
  Serial.println(maxIndex); 

  Serial.println((stepsJ1 / jointTimes[maxIndex])); 
  Serial.println((stepsJ2 / jointTimes[maxIndex]));
  Serial.println((stepsJ3 / jointTimes[maxIndex]));
  Serial.println((stepsJ4 / jointTimes[maxIndex]));


  joint1.setMaxSpeed( (stepsJ1 / jointTimes[maxIndex]) );
  joint2.setMaxSpeed( (stepsJ2 / jointTimes[maxIndex]) );
  joint3.setMaxSpeed( (stepsJ3 / jointTimes[maxIndex]) );
  joint4.setMaxSpeed( (stepsJ4 / jointTimes[maxIndex]) );


  joint1.move(stepsJ1);
  joint2.move(stepsJ2);  
  joint3.move(stepsJ3);  
  joint4.move(stepsJ4);  

   while ( 
    (joint1.distanceToGo() != 0) || 
    (joint2.distanceToGo() != 0) ||
    (joint3.distanceToGo() != 0) ||
    (joint4.distanceToGo() != 0) 
    ) {
      joint1.run();
      joint2.run();
      joint3.run();
      joint4.run();
  }
} 

void moveJoint(AccelStepper joint, float angle, int acceleration, float ratio) {  
  int steps = angleToSteps(angle) * ratio;

  joint.setAcceleration(acceleration);
  joint.move(steps);

  while (joint.distanceToGo() != 0) {
      joint.run();
  }
} 

#endif
