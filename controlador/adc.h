#include <wiring_private.h>  //funções sbi() e cbi() do arduino

uint8_t NextADCchannel=1;

void changeADCchannel()
{
  ADMUX = (1 << REFS0) | NextADCchannel;
  sbi(TIFR1, OCF1B); // clear Compare Match B interrupt to start next conversion
  NextADCchannel = !NextADCchannel;
}

void initADC()
{
  ADCSRA = 0;
  ADCSRB = 0;
  ADMUX = 0;
  sbi(ADCSRA, ADPS0);   // set ADPS0 bit for 128 prescalar (125khz ADC clock @16Mhz)
  cbi(ADCSRA, ADPS1);   // set ADPS1 bit for 128 prescalar
  sbi(ADCSRA, ADPS2);   // set ADPS2 bit for 128 prescalar
  sbi(ADCSRA, ADEN);    // enable ADC
  sbi(ADCSRA, ADIE);    // enable ADC interrupt
  sbi(ADCSRA, ADATE);   // enable auto-trigger
  sbi(ADCSRB, ADTS0);   // set ADTS0 bit for auto-trigger source: Timer/Counter1 Compare Match B
  sbi(ADCSRB, ADTS2);   // set ADTS2 bit for auto-trigger source: Timer/Counter1 Compare Match B
  sbi(ADMUX, REFS0);    // set reference voltage

  OCR1B   = 56;         // set Compare Match B register for 100us timer (@16MHz, 8 prescaler)
  TCCR1A  = 0;          // initialize TCCR1A
  TCCR1B  = 0;          // initialize TCCR1B
  sbi(TCCR1B, WGM12);   // turn on CTC mode
  sbi(TCCR1B, CS11);    // set CS11 bit for 8 prescaler

  sei();
}
