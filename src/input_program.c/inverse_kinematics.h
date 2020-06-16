#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

#include <Arduino.h>
#include <math.h>

#define DEG_PER_RAD 57.29577951

#define L0 0.095
#define L1 0.06
#define L2 0.181
#define L3 0.175
#define L4 0.054

	// Main inverse kinematics computation function.
	// Returns joint angles and takes orientation (phi) and x, y, z coordinates
	void inverseKinematics(float phi, float pos[], float jointAngles[4]) {

	    // Intermediate desired location at joint 4
	    const float pos_prime[] = { (pos[0] - L4 * cos(phi)),
	                        pos[1],
	                        (pos[2] - L4 * sin(phi)) };

	    // Intermediate lengths for connecting triangles
	    float alpha_1 = pos_prime[0];
	    float alpha_2 = pos_prime[2] - L0 - L1;
	    float alpha_3 = sqrt( pow(alpha_1, 2) + pow(alpha_2, 2) );

	    // Intermediate angles for geometric helping triangles
	    float phi_1 = acos( 0.5 * alpha_3 / L2 );
	    float phi_2 = atan( alpha_2 / alpha_1 );
	    float phi_3 = PI - 2 * phi_1;

	    // Final joint space angles
	    float theta_1 = ( atan(pos[1] / pos[2]) );
	    float theta_2 = ( phi_1 + phi_2 );
	    float theta_3 = ( PI + phi_3 );
	    float theta_4 = ( 2*PI + (phi - (theta_2 + theta_3)) );

			// Modify passed array to include each joint angle
	    jointAngles[0] = DEG_PER_RAD * theta_1;
	    jointAngles[1] = DEG_PER_RAD * theta_2;
	    jointAngles[2] = 360 - DEG_PER_RAD * theta_3;
	    jointAngles[3] = DEG_PER_RAD * theta_4;
	}


#endif
