clc;  close all;  clear all
C=680e-6;   tau=14;

ModeloMotor;    % recebe a impedância Zl

ControlBuck  % recebe a função de transf. em
             % MF por corrente conversor buck
ControlBoost % recebe a função de transf. em
             % MF por corrente conversor boost
             
Isistema = feedback( 1/(tau*s+1) * Cpi_bu*Ibuck ...
                + (1-1/(tau*s+1))* Cpi_bo*0.9*Iboost...
                                             , filtro);
step(Isistema);  %Corrente total sistema
disp('Malha de tensão do sistema');
Vbus = Isistema/(s*C+1/Zl);
pause();

ws = 2*pi/26e-6;        %taxa de amostragem = 26us
filtro = 1/(1+s/(ws/10));  %banda máx ~ 2,4e4 rad/s
Cpi = 1.5 + 1200/s;       %controlador projetado
controlSystemDesigner(Vbus, Cpi, filtro);
% => Exportar C para Cpi

pause();
Vfixa = feedback(Cpi*Vbus,filtro);
step(Vfixa);
