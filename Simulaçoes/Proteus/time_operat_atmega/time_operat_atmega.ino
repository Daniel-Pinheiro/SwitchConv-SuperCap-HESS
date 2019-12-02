/*Código para teste de demora(ciclo de máquina) para diversas operações entre variáveis. Visualização para simulação no software Proteus*/
/*Selecinada a placa Arduino Nano, dê Ctrl+Alt+S na IDE do Arduino para compilar e gerar o arquivo binario deste programa e poder simula-lo*/

long a=867, b=2678, c=349, d=796, e=127;
long r, s, u, v, x, y, z;
uint16_t g;

uint8_t PROGMEM const lut[]= {10,205465,6544,6546,46,46,46,43,1,351,35,353,135,153,531,35,135,1,5135,1,31,31,31,515,31,3,1,1,531,1,31,5,135,6,351,51,351,351,351,351,351,35,53,13,1,351,351,531,351};
void setup() {
  Serial.begin(9800);
  DDRB=1;
  PINB = 1;
  r = a+b;
  PINB = 1;

  PINB = 1;
  s = a-c;
  PINB = 1;

  PINB = 1;
  u = b+s;
  PINB = 1;

  delayMicroseconds(10);

  PINB = 1;
  v = c*d;
  PINB = 1;

  PINB = 1;
  x = e*v;
  PINB = 1;
  
  PINB = 1;
  y = b<<13;
  PINB = 1;

  delayMicroseconds(10);
  
  PINB = 1;
  z = b/e;
  PINB = 1;

  PINB = 1;
  r = b/y;
  PINB = 1;
  
  PINB = 1;
  x = d>>17;
  PINB = 1;

  PINB = 1;
  g=lut[0];
  PINB = 1;

  PINB = 1;
  g = 256/g;
  PINB = 1;

}

void loop() {
  // put your main code here, to run repeatedly:

}
