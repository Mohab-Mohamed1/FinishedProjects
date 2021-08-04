/*
 * Timer1.c
 *
 * Created: 12/23/2020 11:08:28 PM
 *  Author: Mohab
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ovfCounter = 0;
volatile uint8_t sendFlag = 0;

void timerInit(void)
{
	TCCR1B = 0x05; // prescalar = clk/1024 (16MHz/1024 = 64 us, 1sec = 15625 tick)
	TIMSK = 0x04;  // enable interrupt
	TCNT1 = 18660;
}

ISR(TIMER1_OVF_vect)
{
	cli();
    TCNT1 = 49911;
	sendFlag = 1;
	sei();
}
