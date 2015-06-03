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
	interrupt_enable = true;
	interrupt_flag = false;
	auto_trg_enable = true;
	start_enable = false;
	adc_enable = true;
	triger_source = FREE_RUNNING_MODE;
	mode = FREE_RUNING_INTERRUPT_MODE;
	
	change_mode(mode);
}

void ADC_ConfigurationClass::configure_single_shot()
{
	reset_ADC_register();
	ADMUX |= ((input_chanel) | (voltage_referance << REFS0) | (result_adj_left << ADLAR));
	ADCSRA |= ((prescalar_selection << ADPS0));
}

void ADC_ConfigurationClass::configure_freerun_intrerrupt_mode()
{
	reset_ADC_register();
	ADMUX |= ((input_chanel) | (voltage_referance << REFS0) | (result_adj_left << ADLAR));
	ADCSRA |= ((prescalar_selection << ADPS0) | (interrupt_enable << ADIE) | (auto_trg_enable << ADATE));
}

void ADC_ConfigurationClass::configure_freerun_auto_trigger_mode()
{
	ADMUX |= ((input_chanel) | (voltage_referance << REFS0) | (result_adj_left << ADLAR));
	ADCSRA |= ((prescalar_selection << ADPS0) | (auto_trg_enable << ADATE) | (triger_source));
}

void ADC_ConfigurationClass::reset_ADC_register()
{
	ADMUX = 0x00;
	ADCSRA = 0x80;
	ADCSRB = 0x00;
}

void ADC_ConfigurationClass::change_mode(uint8_t _mode)
{
	if (_mode == SINGLE_SHOT_MODE)
	{
		configure_single_shot();
	} 
	else if(_mode== FREE_RUNING_INTERRUPT_MODE)
	{
		configure_freerun_intrerrupt_mode();
	}
	
}
ADC_ConfigurationClass ADC_Configuration;

void ADC_Enable()
{
	
	ADCSRA |= (1<<ADEN);
}