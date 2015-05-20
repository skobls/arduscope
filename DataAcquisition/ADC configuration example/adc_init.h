// adc_init.h

#ifndef _ADC_INIT_h
#define _ADC_INIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


void initADCinttrerupmode();
void startConvertion();


#endif

