#include "config.h"
#include "SevenSegment.h"

unsigned char segmentNumbers[SIZE] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void sevenSegmentInit(void)
{
    // Pin3 & Pin 4 are outputs which are connected
    // to Disp 3 and Disp 4 respectively
    TRISAbits.TRISA4 = 0 ;
    TRISAbits.TRISA5 = 0 ;
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 1;
    // Setting all pins in portD as output
    TRISD = 0x00;
    PORTD = 0x00;
}

void sevenSegmentOFF(void)
{
    PORTAbits.RA4 = 0;
    PORTAbits.RA5 = 0;
    
    TRISD = 0x00;
    PORTD = 0x00;
}

void setDisplay(unsigned char num)
{
    unsigned char firstNumber = num / 10;
    unsigned char secondNumber = num % 10;
    
    PORTAbits.RA4 = 1;
    PORTAbits.RA5 = 0;
    PORTD = segmentNumbers[firstNumber];
    __delay_ms(1);
    
    PORTAbits.RA4 = 0;
    PORTAbits.RA5 = 1;
    PORTD = segmentNumbers[secondNumber];
    __delay_ms(1);
}


