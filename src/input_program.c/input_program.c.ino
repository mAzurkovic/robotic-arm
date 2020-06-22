#include <AccelStepper.h>
#include "motors.h"
#include "inverse_kinematics.h"

#define LARGE_RATIO 28.44
#define SMALL_RATIO 18.78

#define INTERFACE_TYPE 1

#define J1_DIR  4
#define J1_STEP 5

#define J2_DIR  8
#define J2_STEP 9

#define J3_DIR  11
#define J3_STEP 12

#define J4_DIR  6
#define J4_STEP 7

String inString;

float jointAngles[4];
float prevAngles[4];
float sendAngles[4];
float pos[3];

AccelStepper J1 = AccelStepper(INTERFACE_TYPE, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(INTERFACE_TYPE, J2_STEP, J2_DIR);
AccelStepper J3 = AccelStepper(INTERFACE_TYPE, J3_STEP, J3_DIR);
AccelStepper J4 = AccelStepper(INTERFACE_TYPE, J4_STEP, J4_DIR);

void goToCoord(float x, float y, float z, float pitch) {
  pos[0] = x;
  pos[1] = y;
  pos[2] = z;
     
  inverseKinematics(pitch, pos, jointAngles);
     
  sendAngles[0] = jointAngles[0] - prevAngles[0];
  sendAngles[1] = jointAngles[1] - prevAngles[1];
  sendAngles[2] = jointAngles[2] - prevAngles[2];
  sendAngles[3] = jointAngles[3] - prevAngles[3];
    
  interpolatedRun(J1, J2, J3, J4, sendAngles, 800);  

  prevAngles[0] = jointAngles[0];
  prevAngles[1] = jointAngles[1];
  prevAngles[2] = jointAngles[2];
  prevAngles[3] = jointAngles[3];  
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

  J4.setMaxSpeed(800.0);
  J4.setAcceleration(800.0);
  
  Serial.println("===========");
  Serial.println("Move Joints");
  Serial.println("===========");
  Serial.println("Enter command in form: <J1,J2,J3,J4> <ANGLE>");

  prevAngles[0] = 0;
  prevAngles[1] = 0;
  prevAngles[2] = 0;
  prevAngles[3] = 0;

  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    inString = Serial.readString();    
    String command = inString.substring(0,2);
    float angle = (inString.substring(3)).toFloat();
    
    if (command.equals("J1")) {
      Serial.println("Moving JOINT 1: " + String(angle) + " degrees");
      moveJoint(J1, angle, 1600, LARGE_RATIO); 
    } else if (command.equals("J2")) {
      Serial.println("Moving JOINT 2: " + String(angle) + " degrees"); 
      moveJoint(J2, angle, 1600, LARGE_RATIO);
    } else if (command.equals("J3")) {
      Serial.println("Moving JOINT 3: " + String(angle) + " degrees"); 
      moveJoint(J3, angle, 1600, LARGE_RATIO);
    } else if (command.equals("J4")) {
      Serial.println("Moving JOINT 4: " + String(angle) + " degrees"); 
      moveJoint(J4, angle, 1600, SMALL_RATIO);
    } else if (command.equals("MV")) {
      float xpos = (inString.substring(3,7)).toFloat();
      float ypos = (inString.substring(8,12)).toFloat();
      float zpos = (inString.substring(13)).toFloat();

      goToCoord(xpos, ypos, zpos, 0);

    } else if (command.equals("GO")) {
      goToCoord(0.20, 0, 0.20, 0);
      goToCoord(0.15, 0.05, 0.15, 0);
      goToCoord(0.20, -0.05, 0.25, 0);
      goToCoord(0.30, 0.1, 0.15, 0);
      
    } else if (command.equals("OK")) {
      goToCoord(0.20, 0, 0.20, 0);
      goToCoord(0.20, 0, 0.20, 45);
    }

  }

}
