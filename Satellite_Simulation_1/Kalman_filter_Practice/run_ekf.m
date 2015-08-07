clear all; close all; clc;

Q = 0.05*eye(2); %process noise covariance
L = chol(Q); %cholesky factorization

R = 0.5; %measurement noise variance

x0 = [0;10]; %actual initial state
x0_guess = [0;15]; %initial state guess

P0_guess = [0,0;0, 15]; %initial covariance guess

%% Dynamics
A = [0, 1; 0, 0];
B = [0;1];
C = [1,0];
D = 0;

dt = 0.05;

sys = ss(A,B,C,D);
sys_d = c2d(sys,dt,'zoh');
Ad = sys_d.A;
Bd = sys_d.B;
