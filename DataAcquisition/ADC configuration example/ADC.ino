#include "adc_init.h"





void setup()
{
  Serial.begin(9600);
  cli();
  initADCinttrerupmode();
  startConvertion();
  sei();

}

void loop()
{



}

