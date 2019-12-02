disp('Malha de corrente do Conversor buck');

Ibuck = BuckFT(Zl);  %carga como imped do motor
%bode(Ibuck);    %resposta em freq. malha aberta
%pause();

ws = 2*pi/26e-6;        %taxa de amostragem = 26us
filtro = 1/(1+s/(ws/10));  %banda máx ~ 2,4e4 rad/s 
Cpi_bu = 0.42 + 1100/s;       %controlador projetado
%controlSystemDesigner(Ibuck, Cpi_bu, filtro);
% => Exportar C para Cpi_bu

%função de transf. com entrada de impedância
function H = BuckFT(Z)% = Il(s)/D(s)
Vs = 7.2;   Rs=50e-3;
L = 200e-6;    C=680e-6;

s = tf('s');
Vc = Vs / (s^2*L*C + s*(Rs*C+L/Z) + (1+Rs/Z));
H = (s*C+1/Z)*Vc;
end