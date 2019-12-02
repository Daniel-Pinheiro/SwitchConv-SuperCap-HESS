clc;    clear all

fc = 200;    %frequência de corte
fs = 1000;  %frequência de amostragem
[b,a] = butter(3,fc/(fs/2));
a;  %coeficientes da função de transf.
b;  % de um filtro butterworth de 3a ord
freqz(b,a)  %resposta em frequência

figure
dataIn = randn(1000,1); %gera sinal aleatório
dataOut = filter(b,a,dataIn);   %filtra sinal
t = 1:1000;
plot(t,dataIn,'b',t,dataOut,'r')
%compara resultado do sinal orig. com o filtrado