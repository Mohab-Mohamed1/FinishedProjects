/*
 * ADC_Functions.c
 *
 * Created: 12/22/2020 6:07:12 PM
 *  Author: Mohab
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_Config.h"


volatile uint8_t conversionCompleted = 0;

void ADC_Init(void)
{
	DDRA = 0x00;
	ADMUX = 0x00;
	ADMUX |= (1 << 6); // AVCC with external cap at AREF
	ADMUX |= (1 << 5); // The result is left adjusted (ADCH)
	
	
	ADCSRA = 0x00;
	//ADCSRA |= (1 << 5); // ADC auto triggering mode
	ADCSRA |= (1 << 2) | (1 << 1) | (1 << 0); // prescaler = clock /128
	//ADCSRA |= (1 << 3);	// ADC Interrupt enable
	
	SFIOR = 0x00;
	SFIOR &= 0x1F;	// Free running mode
	
	
	
}

void ADC_Select(uint8_t channel)
{
	ADCSRA &= ~(1 << 7); // ADC Disable
	ADMUX = (ADMUX & 0xF8) | channel; // choose channel;
	ADCSRA |= (1 << 7); // ADC enable
	ADCSRA |= (1 << 6); // Start Conversion
}

uint8_t ADC_isConversionComplete(void)
{
	return ((ADCSRA & 0x10) == 0) ? 0 : 1;
}

ISR(ADC_vect)
{
	cli();
	conversionCompleted = 1;
	sei();
}
