// 
// 
// 

#include "ADC_Configuration.h"

void ADC_ConfigurationClass::init()
{
	input_chanel = CHANEL_0;
	voltage_referance = REFERENCE_AVCC;
	result_adj_left = false;

	prescalar_selection = DIV_FACTOR_128;
	inttrerupt_enable = true;
	inttrerupt_flag = false;
	auto_trg_enable = true;
	start_enable = false;
	adc_enable = true;
	triger_source = FREE_RUNNING_MODE;
	mode = FREE_RUNING_INTERRUPT_MODE;
	
	change_mode(mode);
}

void ADC_ConfigurationClass::change_mode(uint8_t _mode)
{
	
	
}
ADC_ConfigurationClass ADC_Configuration;

void ADC_Enable()
{
	
	ADCSRA |= (1<<ADEN);
}