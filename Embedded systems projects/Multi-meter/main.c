/*
 * main.c
 *
 * Created: 12/22/2020 12:05:47 PM
 *  Author: Mohab
 */ 

#include <avr/io.h>
#include "avr/interrupt.h"
#include "uart.h"
#include "ADC_Config.h"
#include "Multimeter.h"

#undef F_CPU
#define F_CPU 16000000UL
#include <util/delay.h>



int main(void)
{
	SystemInit();
	sei();
    while(1)
    {
		OpModeChange();
		SendvDF();
		SendcDF();
		SendrDF();
	}
}