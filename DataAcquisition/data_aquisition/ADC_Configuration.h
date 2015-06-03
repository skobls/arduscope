// ADC_COnfiguration.h

#ifndef _ADC_CONFIGURATION_h
#define _ADC_CONFIGURATION_h

#include <avr/sfr_defs.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Define input_chanels

#define CHANEL_0 0
#define CHANEL_1 1 
#define CHANEL_2 2
#define CHANEL_3 3 
#define CHANEL_4 4
#define CHANEL_5 5 
#define CHANEL_6 6 
#define CHANEL_7 7 

//Define Voltage reference

#define REFERENCE_AREF 0 //internal Vref turned OFF
#define REFERENCE_AVCC 1 //AVCC with capacitor on Aref
#define REFERENCE_1V1 2
#define REFERENCE_2V56 3

// Define modes
#define SINGLE_SHOT_MODE 0
#define FREE_RUNING_INTERRUPT_MODE 1
#define FREE_RUNING_AUTO_TRIGGER_MODE 2

//Define prescalar value
#define DIV_FACTOR_2	1
#define DIV_FACTOR_4	2
#define DIV_FACTOR_8	3
#define DIV_FACTOR_16	4
#define DIV_FACTOR_32	5
#define DIV_FACTOR_64	6
#define DIV_FACTOR_128	7	

//Define triger sources

#define FREE_RUNNING_MODE	0
#define ANALOG_COMPARATOR	1
#define EXTERNAL_INTR_R0	2
#define TIMER0_COMP_A		3
#define TIMER0_OWER			4
#define TIMER1_COMP_B		5
#define TIMER1_OWER			6
#define TIMER1_CAPTURE_EVENT	7

//#define 

class ADC_ConfigurationClass
{
 public:
	//ADMUX ADC Multiplexer Selection Register
	uint8_t input_chanel;
	uint8_t voltage_referance;
	boolean result_adj_left;
	
	//AADCSRA – ADC Control and Status Register A
	uint8_t prescalar_selection;
	uint8_t interrupt_enable; 
	uint8_t interrupt_flag;
	uint8_t auto_trg_enable;
	uint8_t	start_enable;
	uint8_t adc_enable;
	
	//ADCSRB – ADC Control and Status Register B
	uint8_t triger_source;	
	
	//Working mode
	uint8_t mode;

	void init();
	void change_mode(uint8_t _mode);
	void refresh_mode();
	void set_intt_mode();
	void configure_single_shot();
	void configure_freerun_intrerrupt_mode();
	void configure_freerun_auto_trigger_mode();
	void reset_ADC_register();
	void Start_Conversion();
	//read functions
};

extern ADC_ConfigurationClass ADC_Configuration;

void ADC_Enable();

#endif



