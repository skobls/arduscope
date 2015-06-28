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
/*******************
#define CHANEL_0 0
#define CHANEL_1 1 
#define CHANEL_2 2
#define CHANEL_3 3 
#define CHANEL_4 4
#define CHANEL_5 5 
#define CHANEL_6 6 
#define CHANEL_7 7 
*********************/
enum IMPUT_CHANEL : uint8_t {
								CHANEL_0 = 0,
								CHANEL_1,
								CHANEL_2,
								CHANEL_3,
								CHANEL_4,
								CHANEL_5,
								CHANEL_6,
								CHANEL_7
							};
//Define Voltage reference

/*****
#define REFERENCE_AREF 0 //internal Vref turned OFF
#define REFERENCE_AVCC 1 //AVCC with capacitor on Aref
#define REFERENCE_1V1 2
#define REFERENCE_2V56 3
*****/

enum REFERENCE : uint8_t {
							AREF = 0,
							AVCC,
							_1V1,
							_2V56
						};

// Define modes
/****
#define SINGLE_SHOT_MODE 0
#define FREE_RUNING_INTERRUPT_MODE 1
#define FREE_RUNING_AUTO_TRIGGER_MODE 2
*****/
enum MODE : uint8_t {
	
	SINGLE_SHOT_MODE = 0,
	FREE_RUNING_INTERRUPT_MODE,
	FREE_RUNING_AUTO_TRIGGER_MODE	
	};

//Define prescalar value
/****
#define DIV_FACTOR_2	1
#define DIV_FACTOR_4	2
#define DIV_FACTOR_8	3
#define DIV_FACTOR_16	4
#define DIV_FACTOR_32	5
#define DIV_FACTOR_64	6
#define DIV_FACTOR_128	7	
****/
enum DIV_FACT : uint8_t {
	Div2 = 1,
	Div4,
	Div8,
	Div16,
	Div32,
	Div64,
	Div128	
	};
//


//Define triger sources
/*****
#define FREE_RUNNING_MODE	0
#define ANALOG_COMPARATOR	1
#define EXTERNAL_INTR_R0	2
#define TIMER0_COMP_A		3
#define TIMER0_OWER			4
#define TIMER1_COMP_B		5
#define TIMER1_OWER			6
#define TIMER1_CAPTURE_EVENT	7
****/
enum TRIGER_SOURCE : uint8_t{
	FREE_RUNNING_MODE = 0,
	ANALOG_COMPARATOR,
	EXTERNAL_INTR_R0,
	TIMER0_COMP_A,
	TIMER0_OWER,
	TIMER1_COMP_B,
	TIMER1_OWER,
	TIMER1_CAPTURE_EVENT
	};
	
enum TIME_DIVISION_256 : uint16_t {
	_100us = 6,
	_500us = 31,
	_1ms = 62,
	_2ms = 125,
	_5ms = 312,
	_10ms = 625,
	_20ms = 1250,
	_50ms = 3125, 
	_100ms = 6250,
	_500ms = 31250,
	_1s = 62500
	};
	
// define the timer 1 parameters.

enum TIMER_PRESCALER : uint8_t {
	STOP_TIMER = 0,
	Presc1,
	Presc_8,
	Presc_64,
	Presc_256,
	Presc_1024,
	EXT_CLK_FALL,
	EXT_CLK_RISE
	};

class ADC_ConfigurationClass
{
 public:
	
	//ADMUX ADC Multiplexer Selection Register
	IMPUT_CHANEL input_chanel;
	REFERENCE voltage_referance;
	bool result_adj_left;
	
	//AADCSRA – ADC Control and Status Register A
	DIV_FACT prescalar_selection;
	bool interrupt_enable; 
	//uint8_t interrupt_flag;
	bool auto_trg_enable;
	bool start_enable;
	bool adc_enable;
	
	//ADCSRB – ADC Control and Status Register B
	TRIGER_SOURCE triger_source;	
	
	//Working mode
	MODE mode;
	
	// timer stuff
	TIMER_PRESCALER timer_prescaler;
	TIME_DIVISION_256 time_division_256;
	

	void init();
	void change_mode();
	void refresh_mode();
	void configure_single_shot();
	void configure_freerun_intrerrupt_mode();
	void configure_freerun_auto_trigger_mode();
	void reset_register();
	void Start_Conversion();		// start and stop is  for intrerrupt mode and auto triger
	void Stop_Conversion();			//
	uint16_t readValue (uint8_t); //just for single shote mode
	
	//read functions
};



extern ADC_ConfigurationClass ADC_Configuration;


void ADC_Enable();

#endif



