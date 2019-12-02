#include "pwm.h"

#define BT_high PORTD6  //IO6
#define BT_low  PORTD5  //IO5
#define SC_low  PORTB3  //IO11
#define SC_high  PORTD3  //IO3

uint8_t dutyBT=0, dutySC=255;

void ConvSincrBuck::config()
{
  cbi(TCCR0B, CS00);    cbi(TCCR0B, CS01);   cbi(TCCR0B, CS02); //No clock source (Timer/Counter stopped)
  sbi(DDRD, BT_low);    // PD5 output
  sbi(DDRD, BT_high);   // PD6 output
  OCR0A = dutyBT;
  OCR0B = dutyBT;
  
    /*Timer0*/
  sbi(TCCR0A, COM0A1);  cbi(TCCR0A, COM0A0);                    // Clear OC0A on Compare Match, set OC0A at BOTTOM, (non-inverting mode).
  sbi(TCCR0A, COM0B1);  sbi(TCCR0A, COM0B0);                    // Set OC0B on Compare Match, clear OC0B at BOTTOM,(inverting mode).
  sbi(TCCR0A, WGM01);   sbi(TCCR0A, WGM00);                     // Fast PWM Mode
  cbi(TCCR0B, WGM02);                                           // TCNT0(min)=0x00 and TCNT0(max)=0xFF
  sbi(TCCR0B, CS00);                                            // clk(No prescaling)
}

void ConvSincrBuck::setDutyCicle(uint8_t duty)
{
  OCR0A = duty;
  OCR0B = duty;
}

void ConvSincrBoost::config()
{
  turnOff();
  cbi(TCCR2B, CS20);    cbi(TCCR2B, CS21);   cbi(TCCR2B, CS22); // No clock source (Timer/Counter stopped)
  sbi(DDRB, SC_low);   // PB3 output
  sbi(DDRD, SC_high);    // PD3 output
  OCR2A = dutySC;
  OCR2B = dutySC;
  
    //Timer2
  sbi(TCCR2A, COM2A1);  sbi(TCCR2A, COM2A0);                    // Clear OC2A on Compare Match, set OC2A at BOTTOM,(inverting mode).
  sbi(TCCR2A, COM2B1);  cbi(TCCR2A, COM2B0);                    // Set OC2B on Compare Match, clear OC2B at BOTTOM, (non-inverting mode).
  sbi(TCCR2A, WGM21);   sbi(TCCR2A, WGM20);                     // Fast PWM Mode (10bits)
  cbi(TCCR2A, WGM22);                                           // TCNT2(min)=0x00 and TCNT2(max)=0xFF
  sbi(TCCR2B, CS20);                                            // clk(No prescaling)
}

void ConvSincrBoost::setDutyCicle(uint8_t duty)
{
  OCR2A = duty;
  OCR2B = duty;
}

void ConvSincrBoost::turnOn()
{
  PORTB |= 2;
}

void ConvSincrBoost::turnOff()
{
  PORTB &= ~2;
}
