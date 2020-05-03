% Test and simulate the inverse kinematics formulas

clear all;

%%%%%%%%%%
% Inputs %
%%%%%%%%%%

p = [ 0.11496 0.0 0.09877 ]; % x0, y0, z0 desired positions
phi = 0; % Desired end-effector joinmt angle follower

% Constants
L0      = 0.01;   
L1      = 0.045;
L2      = 0.15;
L3      = 0.15;
L4      = 0.03;

p_prime = [ (p(1) - L4 * cosd(phi)) p(2) (p(3) - L4 * sind(phi))];

% Intermediate lengths for connecting triangles
alpha_1 = p_prime(1);
alpha_2 = p_prime(3) - L0 - L1;
alpha_3 = sqrt(alpha_1^2 + alpha_2^2);

% Intermediate angles for geometric helping triangles
phi_1 = acosd( 0.5 * alpha_3 / L2 );
phi_2 = atand( alpha_2 / alpha_1 ); 
phi_3 = 180 - 2 * phi_1;

% Final joint space angles
theta_1 = atand(p(2) / p(3));
theta_2 = phi_1 + phi_2;
theta_3 = 180 + phi_3;
theta_4 = 360 + (phi - (theta_2 + theta_3));

joint_space = [ theta_1 ; theta_2 ; theta_3 ; theta_4 ];

disp(phi_3);

disp(joint_space);