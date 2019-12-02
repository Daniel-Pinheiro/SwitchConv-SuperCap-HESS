close all;  clear all

D = .666;%8/12;
V = 8;        R = 0.2;
L = 120e-6;   C= 200e-6;
I = 5;        T=30e-3;
Ts = 1/62.5e3;

s = tf('s');
Vc = (V*1^2) / (L*C*s^2 + R*C*s + 1^2);
bode(Vc);
hold on

Vc1 = (V*.9) / (L*C*s^2 + R*C*s + .9^2);
bode(Vc1);
Vc2 = (V*.7) / (L*C*s^2 + R*C*s + .7^2);
bode(Vc2);
Vc3 = (V*.5) / (L*C*s^2 + R*C*s + .5^2);
bode(Vc3);
Vc4 = (V*.3) / (L*C*s^2 + R*C*s + .3^2);
bode(Vc4);
hold off

% Il = I*(R+s*L)*exp(-s*T) / Den;
% planta = Vc -I*Id*18;
% step(planta, Td+30e-3);
sensor = zpk(1/(1+s*10*Ts/(2*pi))^2);
% 
% zpk(1/Vc)
%controlSystemDesigner;
% pause();
% pidtool(sys0*filtro/12)  % => Exported to Cpid
% pause();
% 
% Cpid
% sys1 = 12*feedback(Cpid*(Vc-Id)/12,filtro);
% step(sys1, T+30e-3);
