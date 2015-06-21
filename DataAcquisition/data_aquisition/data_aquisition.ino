#include "ADC_COnfiguration.h"
#include <avr/interrupt.h>
volatile int valoare=0;
bool flag_print = false;

ADC_ConfigurationClass inst1;

void setup()
{
	//pinMode(13, OUTPUT);
	ADC_Enable();
	Serial.begin(9600);
	inst1.init();
	//inst1.change_mode(FREE_RUNING_AUTO_TRIGGER_MODE);
	inst1.Start_Conversion();
		
	
	
	
  /* add setup code here */

}

void loop()
{
	
  /* add main program code here */
if (flag_print)
{
	Serial.println((float(valoare) * 5)/1024);
	flag_print = false;	
}

}

ISR(ADC_vect)
{
	
	valoare = ADC;
	flag_print = true;

}
