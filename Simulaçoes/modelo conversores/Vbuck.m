clc;  close all;  clear all

Td=50e-3;   D = 5/7.2; %Dutycicle = 69,4%

s = tf('s');
sistema = D*BuckFT(1e3);         
step(sistema, Td);

figure();
sistema = D*BuckFT(1);         
step(sistema, Td);

function H = BuckFT(Z)% = Vc(s)/D(s)
Vs = 7.2;   Rs=50e-3;
L = 200e-6;    C=680e-6;

s = tf('s');
H = Vs / (s^2*L*C + s*(Rs*C+L/Z) + (1+Rs/Z));
end