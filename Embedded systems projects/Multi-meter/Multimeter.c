/*
 * Multimeter.c
 *
 * Created: 12/22/2020 10:00:53 AM
 *  Author: Mohab
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#undef F_CPU
#define F_CPU 16000000UL
#include <util/delay.h>
#include "ADC_Config.h"
#include "uart.h"
#include "Timer1.h"

#undef F_CPU
#define F_CPU 16000000UL

#define Op_buffer_start 0
#define Op_buffer_data 1
#define  Op_buffer_end 2
#define Op_buffer_len 3

#define Data_buffer_start 0
#define Data_buffer_end 5
#define Data_buffer_len 6

#define NULL_MODE 0
#define VOLTAGE_MODE 1
#define CURRENT_MODE 2
#define RESISTANCE_MODE 3
#define DUAL_MODE 4

static uint8_t Op_buffer[Op_buffer_len]; // array that receives the frame that tells what mode the atmega operates in.
static uint8_t cData_buffer[Data_buffer_len]; // array that carries the current result to pc.
static uint8_t vData_buffer[Data_buffer_len]; // array that carries the voltage result to the pc.
static uint8_t rData_buffer[Data_buffer_len]; // array that carries the resistance result to pc.
uint16_t ADC_val;
uint8_t OpMode = NULL_MODE; // stores the operation mode identifier value.
uint8_t rcvFlag = 0;


/*
	we can use channel0~3: channels 0 and 1 are used to measure voltage when in voltage mode
	while channels 2 and 3 are used to measure current when in current or dual mode
	while channel 3 is use to measure resistance
*/

void SystemInit(void)
{
	ADC_Init();
	timerInit();
	DDRC = 255;
	UART_cfg my_uart_cfg;
	/* Set USART mode. */
	my_uart_cfg.UBRRL_cfg = (BAUD_RATE_VALUE)&0x00FF;
	my_uart_cfg.UBRRH_cfg = (((BAUD_RATE_VALUE)&0xFF00)>>8);
	my_uart_cfg.UCSRA_cfg = 0;
	my_uart_cfg.UCSRB_cfg = (1<<RXEN) | (1<<TXEN) | (1<<TXCIE) | (1<<RXCIE);
	my_uart_cfg.UCSRC_cfg = (1<<URSEL) | (3<<UCSZ0);
	UART_Init(&my_uart_cfg);
}

void OpModeChange(void)
{
	// Receiving frame format #[operation mode byte]#
	if(rcvFlag == 0)
	{
		UART_ReceivePayload(Op_buffer, Op_buffer_len);
		rcvFlag = 1;
	}
	//while(UART_IsRxComplete() == 0);
	if((Op_buffer[Op_buffer_start] == '#') && (Op_buffer[Op_buffer_end] == '#') && (UART_IsRxComplete() == 1))
	{
		rcvFlag = 0;
		if(Op_buffer[Op_buffer_data] == '0') // NULL mode
		{
			PORTC = 0x00;
			OpMode = NULL_MODE ;
		}
		else if(Op_buffer[Op_buffer_data] == '1') // Voltage mode
		{
			PORTC = 0x01; 
			OpMode = VOLTAGE_MODE;
		}
		else if(Op_buffer[Op_buffer_data] == '2') // Current mode
		{
			PORTC = 0x02;
			OpMode = CURRENT_MODE;
		}
		else if(Op_buffer[Op_buffer_data] == '3') // Resistance mode
		{
			PORTC = 0x04;
			OpMode = RESISTANCE_MODE;
		}
		else if (Op_buffer[Op_buffer_data] == '4') // Dual mode
		{
			PORTC = 0x03;
			OpMode = DUAL_MODE;
		}
	}
}

/*
void SendDF(void)
{
	//@xxxx;
	if(sendFlag)
	{
		sendFlag = 0;
		if(conversionCompleted)
		{
			conversionCompleted = 0;
			Data_buffer[Data_buffer_start] = '@';
			uint8_t* ptr = &Data_buffer[1]; // pointer that points at the second index of the data buffer array.
			ADC_val = (ADCH << 2); // ADC_val will store a number from 0~1020 resulting from the adc conversion.
			itoa(ADC_val,ptr,10); // convert the ADC_val from integer to ascii string that is stored at the Data_buffer starting from the second index 
			Data_buffer[Data_buffer_end] = ';'; // replacing the '/0' resulting from itoa function with the end of the frame character ';'
			UART_SendPayload(Data_buffer, Data_buffer_len);
			while (0 == UART_IsTxComplete());
		}
	}
	
}
*/

void SendvDF(void)
{
	//@xxxx; frame format
	if(sendFlag)
	{
		if(OpMode == VOLTAGE_MODE)
		{
			sendFlag = 0;
			ADC_Select(CHANNEL0);
			while(ADC_isConversionComplete() == 0);
			ADC_val = (ADCH << 2);
		
			ADC_Select(CHANNEL1);
			while(ADC_isConversionComplete() == 0);
			ADC_val -= (ADCH << 2);
		
			vData_buffer[Data_buffer_start] = '@';
			uint8_t* ptr = &vData_buffer[1]; // pointer that points at the second index of the data buffer array.
			itoa(ADC_val,ptr,10); // convert the ADC_val from integer to ascii string that is stored at the Data_buffer starting from the second index 
			vData_buffer[Data_buffer_end] = ';'; // replacing the '/0' resulting from itoa function with the end of the frame character ';'
		
			UART_SendPayload(vData_buffer, Data_buffer_len);
			while (0 == UART_IsTxComplete());
		}
		else if(OpMode == DUAL_MODE)
		{
			ADC_Select(CHANNEL0);
			while(ADC_isConversionComplete() == 0);
			ADC_val = (ADCH << 2);
		
			ADC_Select(CHANNEL1);
			while(ADC_isConversionComplete() == 0);
			ADC_val -= (ADCH << 2);
		
			vData_buffer[Data_buffer_start] = '@';
			uint8_t* ptr = &vData_buffer[1]; // pointer that points at the second index of the data buffer array.
			itoa(ADC_val,ptr,10); // convert the ADC_val from integer to ascii string that is stored at the Data_buffer starting from the second index 
			vData_buffer[Data_buffer_end] = ';'; // replacing the '/0' resulting from itoa function with the end of the frame character ';'
		
			UART_SendPayload(vData_buffer, Data_buffer_len);
			while (0 == UART_IsTxComplete());
		}
		
	}
}

// NOTE: this function should be called after SendvDF is called because it clears the send flag anyways
void SendcDF(void)
{
	//#xxxx; frame format
	if(sendFlag)
	{
		if((OpMode == CURRENT_MODE) || (OpMode == DUAL_MODE))
		{
			sendFlag = 0;
			
			ADC_Select(CHANNEL2);
			while(ADC_isConversionComplete() == 0);
			ADC_val = (ADCH << 2);
			
			ADC_Select(CHANNEL3);
			while(ADC_isConversionComplete() == 0);
			ADC_val -= (ADCH << 2);
		
			cData_buffer[Data_buffer_start] = '#';
			uint8_t* ptr = &cData_buffer[1]; // pointer that points at the second index of the data buffer array.
			itoa(ADC_val,ptr,10); // convert the ADC_val from integer to ascii string that is stored at the Data_buffer starting from the second index 
			cData_buffer[Data_buffer_end] = ';'; // replacing the '/0' resulting from itoa function with the end of the frame character ';'
		
			UART_SendPayload(cData_buffer, Data_buffer_len);
			while (0 == UART_IsTxComplete());
		}
	}
}	
	
void SendrDF(void)
{
	if (sendFlag)
	{
		if(OpMode == RESISTANCE_MODE)
		{
			sendFlag = 0;
			
			ADC_Select(CHANNEL3);
			while(ADC_isConversionComplete() == 0);
			ADC_val = (ADCH << 2);
			
		
			rData_buffer[Data_buffer_start] = '$';
			uint8_t* ptr = &rData_buffer[1]; // pointer that points at the second index of the data buffer array.
			itoa(ADC_val,ptr,10); // convert the ADC_val from integer to ascii string that is stored at the Data_buffer starting from the second index 
			rData_buffer[Data_buffer_end] = ';'; // replacing the '/0' resulting from itoa function with the end of the frame character ';'
		
			UART_SendPayload(rData_buffer, Data_buffer_len);
			while (0 == UART_IsTxComplete());
		}
	}
}