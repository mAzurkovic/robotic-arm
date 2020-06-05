#include <AccelStepper.h>
#include "inverse_kinematics.h"

#define BASE_STEPS 200
#define MICRO_STEPS 0.25
#define MAX_SPS 800

#define LARGE_RATIO 28.44
#define SMALL_RATIO 18.78

#define INTERFACE_TYPE 1

#define J1_DIR  4
#define J1_STEP 5
#define J1_ENABLE 6

#define J2_DIR  8
#define J2_STEP 9
#define J2_ENABLE 10

#define J3_DIR  11
#define J3_STEP 12
#define J3_ENABLE 13

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

float jointAngles[4];

AccelStepper J1 = AccelStepper(INTERFACE_TYPE, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(INTERFACE_TYPE, J2_STEP, J2_DIR);
AccelStepper J3 = AccelStepper(INTERFACE_TYPE, J3_STEP, J3_DIR);

int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}


void moveJoints(AccelStepper joint1, AccelStepper joint2, AccelStepper joint3, float * jointAngles, int acceleration) {  
  int stepsJ1 = angleToSteps(jointAngles[0]) * LARGE_RATIO;
  int stepsJ2 = angleToSteps(jointAngles[1]) * LARGE_RATIO;
  int stepsJ3 = angleToSteps(360 - jointAngles[2]) * SMALL_RATIO;


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

void dMotorsRun(float* jointAngles, int velociy, int acceleration) {
  int stepsJ1 = angleToSteps(jointAngles[1]);
  int stepsJ2 = angleToSteps(jointAngles[2]);

  // This logic is executed if acceleration is needed (i.e at start and end of a path)
  if (acceleration != 0) {
    // Configure current kinematics parameters
    J1.setAcceleration(acceleration);
    J2.setSpeed(velociy);
    
    J2.setAcceleration(acceleration);
    J2.setSpeed(velociy);

    // Go to desired position
    J1.move(stepsJ1);
    J2.move(stepsJ2);
    
    while ( 
      (J1.distanceToGo() != 0) || 
      (J2.distanceToGo() != 0) 
    ) {
      J1.run();
      J2.run();
    }

  // Run with no acceleration at set speed
  } else {
    J1.move(stepsJ1);
    J1.setSpeed(velociy);

    J2.move(stepsJ2);
    J2.setSpeed(velociy);

    while ( 
      (J1.distanceToGo() != 0) || 
      (J2.distanceToGo() != 0) 
    ) {
      J1.runSpeed();
      J2.runSpeed();

    }
  }
}



void dMotorsRun2(float* jointAngles, int velociy, int acceleration) {
  int stepsJ1 = angleToSteps(jointAngles[1]);
  int stepsJ2 = angleToSteps(jointAngles[2]);

  // This logic is executed if acceleration is needed (i.e at start and end of a path)
  if (acceleration != 0) {
    // Configure current kinematics parameters
    
    //J1.setAcceleration(acceleration);
    J1.setSpeed(velociy);
    

    // Go to desired position
   J1.move(stepsJ1);

   

    while ( 
      (J1.distanceToGo() != 0)
    ) {

      if (J1.speed() > 800) { J1.setSpeed(800); }
      else { J1.setSpeed(J1.speed() + 2); }
      J1.runSpeed();
    }
  }
}


void run3(int distance, int initialVelocity, int finalVelocity, int acceleration) {
  unsigned long time;
  unsigned long previousAccel = 0;
  int interval = 100;  // # of milliseconds between speed increases
  int makeSpeed;

  J1.move(distance);
  J1.setSpeed(initialVelocity);

   while (J1.distanceToGo() != 0) {
    time = millis();
    if (time > previousAccel + interval) {
      previousAccel = time;

      // Acceleration logic
      if (finalVelocity > initialVelocity) {          // Accelerate
        //J1.setSpeed(J1.speed() + acceleration); 
        makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : J1.speed() + acceleration;
      } else if (finalVelocity < initialVelocity) {   // Deccelerate
        //J1.setSpeed(J1.speed() - acceleration); 
        makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : J1.speed() - acceleration;
      } else {
        //J1.setSpeed(finalVelocity);                   // Run at constant speed  
         makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : finalVelocity;
      }
      J1.setSpeed(makeSpeed);
    }
    J1.runSpeed();
  }

}

void setup() {
    
  Serial.begin(9600);

  //----------------------------------------------------------------
  //  Setting speed and acceleration parameters for each joint
  //----------------------------------------------------------------
  J1.setMaxSpeed(800.0);
  J1.setAcceleration(800.0);

  J2.setMaxSpeed(800.0);
  J2.setAcceleration(800.0);

  J3.setMaxSpeed(800.0);
  J3.setAcceleration(800.0);

  delay(500);

}

void loop() {

  float pos[] = {0.110, 0.0, 0.254};
  inverseKinematics(0, pos, jointAngles);
  Serial.println(jointAngles[1]);
  moveJoints(J1, J2, J3, jointAngles, 1600);









  delay(10000);


}
