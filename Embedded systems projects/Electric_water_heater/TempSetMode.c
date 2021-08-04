#include "config.h"
#include "TempSetMode.h"
#include "Timer.h"
#include "SevenSegment.h"
#include "I2C_EEPROM2.h"

unsigned char upPrevState;
unsigned char upCurrState;
unsigned char downPrevState;
unsigned char downCurrState;
unsigned char targetTemp;
unsigned char display_OFF = 0;
unsigned char E2PROM_flag;

void buttonsInit(void)
{
    /*set button pins as input*/
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    /*enable pull up resistors on button pins*/
    OPTION_REGbits.nRBPU = 0;
    
    // Initialize buttons previous in high state
    upPrevState = 1;
    downPrevState = 1;
    
}

void tempSetMode(void)
{
    upCurrState = PORTBbits.RB1;    // Read bit 1 in portB
    downCurrState = PORTBbits.RB2;  // Read bit 2 in portB
    
    // check for up or down buttons release
    if(((upPrevState == 0) && (upCurrState == 1)) || ((downPrevState == 0) && (downCurrState == 1)))
    {
        SetTemp();
    }
    upPrevState = upCurrState;
    downPrevState = downCurrState;
}

void SetTemp(void)
{
    Timer1_Start();
    Timer2_Start();
    while(T1CONbits.TMR1ON)
    {
        upPrevState = upCurrState;
        downPrevState = downCurrState;
        
        upCurrState = PORTBbits.RB2;  // Read bit 2 in portB
        downCurrState = PORTBbits.RB1;    // Read bit 1 in portB 
    
       
        // check for up or down buttons release
        if((upPrevState == 0) && (upCurrState == 1))
        {
            if(targetTemp < 75)
            {
                Timer1_Restart();
                targetTemp += 5; 
            }
        }
        else if((downPrevState == 0 && downCurrState == 1))
        {
            if(targetTemp > 35)
            {
                Timer1_Restart();
                targetTemp -= 5;
            }
        }
        
        if(display_OFF)
        {
            PORTAbits.RA4 = 0;
            PORTAbits.RA5 = 0;
        }
        else if(!display_OFF)
        {
            setDisplay(targetTemp);
        }
    }
    if(E2PROM_flag == 1)
    {
        E2PROM_flag = 0;
        saveTemp2();
    }
    
}
