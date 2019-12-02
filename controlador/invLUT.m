clc;    clear all

x = 1:2^16; %Vetor com sequ�ncia de n�meros para dom�nio de fun��o

% Vetor de fun��o inversa quadr�tica com ganho de 4095 p/ aumento de resolu��o
y = round((2^12-1)./sqrt(x));

% Automatiza��o da cria��o de c�digo em C p/ AVR com implementa��o de LUT
LUT = fopen('LUTinv.h','w'); %Arquivo de biblioteca a ser incluso.
fprintf( LUT, '#define inv(D) pgm_read_word_near(adressLUT+D)\n\nconst PROGMEM uint8_t adressLUT[] =\n{\n  ');
format shortG

for i = 0:2^10-1
    for j = 1:2^4
        if(y(16*i+j)>255)
            y(16*i+j)=255; %Limita tamanho m�ximo p/ 8 bits.
        end
        fprintf( LUT, '%d, ',y(16*i+j) );
    end
    fprintf( LUT, '\n  ');
end
fprintf( LUT, '};');
fclose(LUT);