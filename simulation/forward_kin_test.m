% Test and simulate the forward kinematics formulas

clear all;

%%%%%%%%%%
% Inputs %
%%%%%%%%%%

theta = [ 45.3545 98.6801 217.1534 44.1665]; % x0, y0, z0 desired positions
phi = 0; % Desired end-effector joinmt angle follower

% Constants
L0      = 0.01;   
L1      = 0.045;
L2      = 0.15;
L3      = 0.15;
L4      = 0.03;

%gamma_2 = L2 * cosd(180 - theta(2));
%gamma_3 = L3 * sind(90 - theta(4));

%delta_2 = L2 * sind(180 - theta(2));
%delta_3 = L3 * cosd(90 - theta(4));

%x = gamma_3 - gamma_2 + L4 * cosd(phi);
%z = delta_2 - delta_3 + L4 * sind(phi);
%%%

x = L2 * cosd(theta(2)) + L3 * cosd( theta(2) + theta(3) ) + L4 * cosd( theta(2) + theta(3) + theta(4) );
z = L2 * sind(theta(2)) + L3 * sind( theta(2) + theta(3) ) + L4 * sind( theta(2) + theta(3) + theta(4) );
y = .1150 * sind(theta(1));

coord = [ x ; y ; z ; ];

disp(coord)