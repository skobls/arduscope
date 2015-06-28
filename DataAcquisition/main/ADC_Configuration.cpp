// 
// 
// 

#include "ADC_Configuration.h"


void ADC_ConfigurationClass::init()
{
	input_chanel = CHANEL_0;
	voltage_referance = AVCC;
	result_adj_left = false;

	prescalar_selection = Div16;
	interrupt_enable = true;
	//interrupt_flag = false;
	auto_trg_enable = true;
	
	start_enable = false;
	adc_enable = true;
	triger_source = TIMER1_COMP_B;
	mode = SINGLE_SHOT_MODE;
	
	timer_prescaler = Presc_256;
	time_division_256 = _100ms;
	
	change_mode();
}

void ADC_ConfigurationClass::configure_single_shot()
{
	
	ADMUX |= ((input_chanel) | (voltage_referance << REFS0) | (result_adj_left << ADLAR));
	ADCSRA |= ((prescalar_selection << ADPS0));
}

void ADC_ConfigurationClass::configure_freerun_intrerrupt_mode()
{
	
	ADMUX |= ((input_chanel) | (voltage_referance << REFS0) | (result_adj_left << ADLAR));
	ADCSRA |= ((prescalar_selection << ADPS0) | (interrupt_enable << ADIE) | (auto_trg_enable << ADATE));
}

void ADC_ConfigurationClass::configure_freerun_auto_trigger_mode()
{
	
	cli();
	ADMUX |= ((input_chanel << MUX0) | (voltage_referance << REFS0) | (result_adj_left << ADLAR) );
	ADCSRA |= ((prescalar_selection << ADPS0) | (auto_trg_enable << ADATE) | (interrupt_enable <<ADIE) );
	ADCSRB |= (triger_source<<ADTS0);
	
	
	OCR1B = time_division_256;
	TCCR1B |= (1<<WGM12); //activating CTC mode of the timer	
	TIMSK1 |= (1<<OCIE1B); //activate the intrrerupt flag b
	
	
	sei();
	
}

void ADC_ConfigurationClass::reset_register()
{
	ADMUX = 0x00;
	ADCSRA = 0x80;
	ADCSRB = 0x00;
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	
}

void ADC_ConfigurationClass::change_mode()
{
	if (mode == SINGLE_SHOT_MODE)
	{
		reset_register();
		configure_single_shot();
	} 
	else if(mode== FREE_RUNING_INTERRUPT_MODE)
	{
		reset_register();
		configure_freerun_intrerrupt_mode();
	}
	else if(mode == FREE_RUNING_AUTO_TRIGGER_MODE)
	{
		reset_register();
		configure_freerun_auto_trigger_mode();
	}
	
}

void ADC_ConfigurationClass::Start_Conversion()
{
	if (mode == FREE_RUNING_INTERRUPT_MODE)
		ADCSRA |= (1<<ADSC);
	else if (mode == FREE_RUNING_AUTO_TRIGGER_MODE)
	{	
		TCCR1B |= ((timer_prescaler<<CS10));
	}
	
}

void ADC_ConfigurationClass::Stop_Conversion()
{
	if (mode == FREE_RUNING_INTERRUPT_MODE)
		ADCSRA &=~(1<<ADSC);
	else if (mode == FREE_RUNING_AUTO_TRIGGER_MODE)
		TCCR1B &= ((~(1<<CS12)) & (~(1<<CS11)) & (~(1<<CS10)) );
	
}

uint16_t ADC_ConfigurationClass::readValue(uint8_t chanel )
{
	
	ADMUX &= ((~(1<<MUX0)) & (~(1<<MUX1)) & (~(1<<MUX2)) & (~(1<<MUX3))& (~(1<<MUX4)));
	ADMUX |= (chanel<<MUX0);
	ADCSRA |= (1<<ADSC);
	while (bit_is_set(ADCSRA, ADSC));
	return ADC;
	
}

ADC_ConfigurationClass ADC_Configuration;


void ADC_Enable()
{
	
	ADCSRA |= (1<<ADEN);
}



