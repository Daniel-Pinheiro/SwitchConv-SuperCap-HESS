disp('Malha de corrente do Conversor boost');

Iboost = BoostFT(Zl);  %carga como imped do motor
%bode(Iboost);    %resposta em freq. malha aberta
%pause();

ws = 2*pi/26e-6;        %taxa de amostragem = 26us
filtro = 1/(1+s/(ws/10));  %banda máx ~ 2,4e4 rad/s 
Cpi_bo = 0.4 + 1000/s;       %controlador projetado
%controlSystemDesigner(Iboost, Cpi_bo, filtro);
% => Exportar C para Cpi_bo

%função de transf. com entrada de impedância
function H = BoostFT(Z)% = Il(s)/Ð(s)
Vs = 6;   Rs=50e-3;
L = 120e-6;    C=680e-6;

s = tf('s');
Vc = Vs / (s^2*L*C + s*(Rs*C+L/Z) + (1+Rs/Z));
H = (s*C+1/Z)*Vc;
end