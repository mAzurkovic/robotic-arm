#include <AccelStepper.h>
#include "inverse_kinematics.h"

#define BASE_STEPS 200
#define MICRO_STEPS 0.25
#define MAX_SPS 800


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

void dMotorsRun(float* jointAngles, int velociy, int acceleration) {
  int stepsJ1 = angleToSteps(jointAngles[1]);
  int stepsJ2 = angleToSteps(jointAngles[2]);

  // This logic is executed if acceleration is needed (i.e at start and end of a path)
  if (acceleration != 0) {
    // Configure current kinematics parameters
    J1.setAcceleration(acceleration);
    J1.setSpeed(velociy);
    
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
 // J1.setAcceleration(400.0);

  J2.setMaxSpeed(800.0);
  J2.setAcceleration(400.0);

  delay(500);

}

void loop() {

  float angles[] = {0, 360, 90, 0};
  float zeroAngles[4] = {0, 0.45, 0.45, 0};
  
  float pos[] = {0.11496, 0.0, 0.09877};
  inverseKinematics(0, pos, jointAngles);

  // Microstep calibration at start of loop
 // dMotorsRun(zeroAngles, 800, 40);

  run3(800, 0, 800, 20);   // Start
    Serial.println(J1.speed());

  run3(800, J1.speed(), 800, 20);
    Serial.println(J1.speed());

  run3(800, J1.speed(), 800, 20);
    Serial.println(J1.speed());

  run3(800, J1.speed(), 0, 20);


  
 // dMotorsRun(angles, 800, 100);
 // dMotorsRun(angles, 800, 100);
 // dMotorsRun(angles, 800, 0);


  /*float pos[] = {0.11496, 0.0, 0.09877};
  inverseKinematics(0, pos, jointAngles);
  moveJoints(jointAngles[1], jointAngles[2]);*/



  delay(1000);

  /*delay(500);
  moveJoints(-180, 360);
  delay(500);
  moveJoints(180, -360);
  delay(25); */


}
