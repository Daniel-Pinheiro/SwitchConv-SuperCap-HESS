#include "Arduino.h"
#include "pwm.h"      //Biblioteca de configuração do timer 0
#include "invLUT.h"   //Biblioteca de inversão via lookup table

#define Imax 5.5
#define Imin -4
//#define Vref int(6*63.883) // = 6/16.03 * 1024

#define resCurrent 37.88 // bits/Amp = 1024 x 185mV / 5V 
#define bImax int(Imax*resCurrent)
#define bImin int(Imin*resCurrent)
#define offsetCurrent 511

#define minVoltAWU -100000
#define maxVoltAWU 328000
#define minCurrentAWU -1000
#define maxCurrentAWU 8400000

int Iref=0, Vref = int(6*63.883), // valor inicial = 6V
int Volt, Iboost;
long iErroVolt=80000, iErroIbuck=0, iErroIboost=66000;

//ConvSincrBuck  buckBT;
ConvSincrBoost boostSC;
/*_______________________________________________________________ */

void controlVoltage() //Malha de controle de tensão de barramento
{
  Volt = ADC;
  int erroVolt = Vref - Volt;
  iErroVolt += erroVolt;  /*Integral do erro*/

  Iref = (erroVolt>>0) + (iErroVolt>>10);
  
  if(Iref > bImax)  { //Saturação de entrada da malha de controle
    Iref = bImax;
    if(iErroVolt > maxVoltAWU)   iErroVolt = maxVoltAWU; //Antiwindup +
  } else
  if(Iref < bImin)  {
    Iref = bImin;
    if(iErroVolt < minVoltAWU)   iErroVolt = minVoltAWU; //Antiwindup -
  }
}
void controlBoostCurrent() //Malha de controle de corrente no indutor
{
  //Iref = int(5*resCurrent); /*No modo corrente constante*/
  Iboost = ADC-offsetCurrent;
  int erroIboost = Iref - Iboost;
  iErroIboost += erroIboost;
  int D = (erroIboost>>0) + (iErroIboost>>8);

  if(D < 0)  {
    D = 0;
    if(iErroIboost < minCurrentAWU)   iErroIboost = minCurrentAWU; //Antiwindup -
  } else
  if(D > 16383)  {  //Limita tamanho máximo da lookup table
    D = 16383;      //(protege contra acesso fora da LUT)
    if(iErroIboost > maxCurrentAWU)   iErroIboost = maxCurrentAWU; //Antiwindup +
  }
  boostSC.setDutyCicle( inv(D) ); // inv() é a macro que implementa a LUT
  /*Atribui o dutycicle do conversor boost como o inverso
   ao quadrado da saída do controlador de corrente*/
}
/*void controlBuckCurrent()
{
  int erroIbuck = Iref - (ADC-offsetCurrent);
  iErroIbuck += erroIbuck;
  uint8_t D = (erroIbuck>>4) + (iErroIbuck>>6);
  
  buckBT.setDutyCicle(D);
}*/
