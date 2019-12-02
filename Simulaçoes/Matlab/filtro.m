clc;    clear all

fc = 200;    %frequ�ncia de corte
fs = 1000;  %frequ�ncia de amostragem
[b,a] = butter(3,fc/(fs/2));
a;  %coeficientes da fun��o de transf.
b;  % de um filtro butterworth de 3a ord
freqz(b,a)  %resposta em frequ�ncia

figure
dataIn = randn(1000,1); %gera sinal aleat�rio
dataOut = filter(b,a,dataIn);   %filtra sinal
t = 1:1000;
plot(t,dataIn,'b',t,dataOut,'r')
%compara resultado do sinal orig. com o filtrado