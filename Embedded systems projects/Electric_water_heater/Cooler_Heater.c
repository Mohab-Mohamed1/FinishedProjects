#include "config.h"
#include "Cooler_Heater.h"
#include "ADC.h"
#include "TempSetMode.h"





void cooler_heaterInit(void)
{
    TRISCbits.TRISC2 = 0 ; // Set cooler pin as output
    TRISCbits.TRISC5 = 0 ; // Set heater pin as output
    PORTCbits.RC2 = 0;      // Cooler off
    PORTCbits.RC5 = 0;      // Heater off
}

void cooler_heaterControl(void)
{
    if(avgTempCalculated)
    {
        avgTempCalculated = 0;
        
        if(avgTemp == targetTemp)
        {
            PORTCbits.RC5 = 0;  // heater off
            PORTCbits.RC2 = 0;  // cooler off
        }
        else if(avgTemp+5 >= targetTemp)
        {
            if(avgTemp >= targetTemp)
            {
                PORTCbits.RC2 = 1;  // cooler on
                PORTCbits.RC5 = 0;  // heater off
            }
            else
            {
                PORTCbits.RC2 = 0;  // cooler off
            }
        }
        
        else if((targetTemp - 5) >= avgTemp )
        {
            if(avgTemp <= targetTemp)
            {
                PORTCbits.RC5 = 1;  // heater on
                PORTCbits.RC2 = 0;  // cooler off
            }
            else
            {
                PORTCbits.RC5 = 0;  // heater off
            }
        }
    }
}
    
    
