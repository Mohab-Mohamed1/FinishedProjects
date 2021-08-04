#include "..//tm4c123gh6pm.h"







// This initialization function sets up the ADC 
// Max sample rate: <=125,000 samples/second
// SS3 triggering event: software trigger
// SS3 1st sample source:  channel 1
// SS3 interrupts: enabled but not promoted to controller

void ADC0_Init(void)
{ 
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC0;
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC0SPD_125K;
	GPIO_PORTE_DIR_R &= ~0x04;
	GPIO_PORTE_DEN_R &= ~0x04;
	GPIO_PORTE_AFSEL_R |= 0x04;
	GPIO_PORTE_AMSEL_R |= 0x04;
	ADC0_SSPRI_R = 0x0123;
	ADC0_ACTSS_R &= ~0x08;
	ADC0_SSMUX3_R &= ~0x0F; 
	ADC0_SSMUX3_R = 0x01;
	ADC0_EMUX_R &= ~0x0000F000;
	ADC0_SSCTL3_R |= 0x06;
	ADC0_ACTSS_R |= 0x08;
	
}

unsigned long ADC0_In(void)
{
	ADC0_PSSI_R |= 0x08;
	while((ADC0_RIS_R & 0x08) == 0);
	ADC0_ISC_R |= 0x08;
  return ((unsigned long) ADC0_SSFIFO3_R & 0x00000FFF); 
}




// Initialize SysTick interrupts to trigger at 40 Hz, 25 ms
void SysTick_Init(unsigned long period)
{
	NVIC_ST_CTRL_R = 0; // disable SysTick
  NVIC_ST_RELOAD_R = period-1;// reload value
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x0FFFFFFF) | 0x40000000;
  NVIC_ST_CTRL_R = 0x07; // enable
}



//********Convert****************
// Convert a 12-bit binary ADC sample into a 32-bit unsigned
// fixed-point distance (resolution 0.001 cm).  Calibration
// data is gathered using known distances and reading the
// ADC value measured on PE1.  
// Overflow and dropout should be considered 
// Input: sample  12-bit ADC sample
// Output: 32-bit distance (resolution 0.001cm)
unsigned long Convert(unsigned long sample)
{
	//return ((unsigned long) 1.016 * sample - 47.5);  // replace this line with real code
	return ((unsigned long) 66 * sample / 4096);	
}








