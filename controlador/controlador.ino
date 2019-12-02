/*  Autor: Daniel Borges
 *  Código para o controlador de conversor chaveado de supercapacitores para um HESS(sistema de armazenamento híbrido de energia).
 *  Software desenvolvido para TCC. Disponível simulação de firmware e hardware no software Proteus.
 *  Selecinada a placa Arduino Nano, dê Ctrl+Alt+S na IDE do Arduino para compilar e gerar o arquivo binario deste programa e poder simula-lo. */
 
#include "main.h"

void setup()  /*Primeira rotina e é executada apenas uma vez*/
{
  boostSC.turnOff();  /*Desativa entrada Enable do conversor boost para evitar pico de corrente reversa*/
  configPins();       /*Configura os I/Os principais do microcontrolador*/
  initADC();          /*inicia o ADC e Configura para operar no modo contínuo e gerar interrupção a cada conversão.*/
  boostSC.config();   /*Configura timer0 no modo 'Fast PWM' para gerar o sinal de controle do conversor boost.*/
  Serial.begin(9600); /*Inicia comunicação serial para envio de caracteres*/
  delay(60);          /*Aguarda um tempo até o controlador se estabilizar*/
  boostSC.turnOn();   /*Ativa entrada Enable(!Shutdown) do conversor boost*/
}

ISR(ADC_vect) /*Rotina que ocorre pela interrupção do ADC*/
{
  changeADCchannel();  /*Alterna entre diferentes canais do ADC programados*/
  PORTB |= 1;
    //O algoritmo de controle ocorre por a cada final de leitura de uma entrada analógica
  if(!NextADCchannel)  controlVoltage();
  else                 controlBoostCurrent();
  PORTB &= ~1;
}

void configPins()
{
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(pinVbus, INPUT);
  pinMode(pinIboost, INPUT);
  
}
