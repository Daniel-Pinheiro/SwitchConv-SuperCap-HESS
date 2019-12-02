clc;  close all;  clear all

Td=25e-3;   D = 6/7; %Dutycicle = 85,7%

s = tf('s');
sistema = 1/D*BoostFT(1e3); %Zl = 1kOhm
step(sistema, Td);

figure();
sistema = 1/D*BoostFT(1);   %Zl = 1Ohm
step(sistema, Td);

function H = BoostFT(Z)% = Vc(s)*D
Vs = 6;   Rs=50e-3;
L = 120e-6;    C=680e-6;

s = tf('s');
H = Vs / (s^2*L*C + s*(Rs*C+L/Z) + (1+Rs/Z));
end