// 
// 
// 

#include "adc_init.h"




int8_t value = 0;

void initADCinttrerupmode()
{
	ADMUX = (1<<REFS0);														 //configure a Voltage reference as Acc an the multiplexer of ADC so in the end we will use A0 pin
	ADCSRA = (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2) | (1<<ADIE);	 //it's enaible the adc, set the prescaler to 128 and and sets to work in interrupt mode
	DIDR0 = (1<<ADC0D);														 // dissable the digital buffer of pin A0
}

void startConvertion()
{
	ADCSRA = (1<ADSC);
}

ISR(ADC_vect)
{
	//value = ADCL;															//takes the result and stored in a variable
	Serial.println(ADCL);
	startConvertion();
	
}

