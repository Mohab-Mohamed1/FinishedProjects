#include "config.h"
#include "ADC.h"

float digitalValue;
unsigned char temp;
unsigned char tempArray[SIZE];
unsigned char index = 0;
unsigned int sum = 0;
unsigned char avgTempCalculated = 0;
unsigned char senseTempFlag = 0;;
char avgTemp = 0;


void ADC_Init(void)
{
   
    // FOSC / 8
    ADCON0bits.ADCS0 = 1;
    ADCON0bits.ADCS1 = 0;
    ADCON1bits.ADCS2 = 0;
    
    // Channel 2
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS2 = 0;
    
    // Result justification
    ADCON1bits.ADFM = 1;
    
    // ADC port configuration control
    ADCON1bits.PCFG0 = 1;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 1;
    
    // Configuring pin as input
    TRISAbits.TRISA2 = 1;
    
    //ADC power on
    ADCON0bits.ADON = 1;
}

void ADC_Read(void)
{
    // Configuring pin as analog input
    TRISAbits.TRISA2 = 1;
    
    // wait of aquisition  time
    __delay_us(30);
    // Start conversion
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE);
    digitalValue = ((unsigned int) ((ADRESH << 8) + ADRESL));
}

void ADC_On(void)
{
    // Configuring pin as input
    TRISAbits.TRISA2 = 1;
    
    //ADC power on
    ADCON0bits.ADON = 1;
}

void ADC_Off(void)
{
    //ADC power on
    ADCON0bits.ADON = 0;
}

void Digital2Temp(unsigned int data)
{
    float analogVolt;
    analogVolt = data * 0.0048828;
    temp = analogVolt / 0.01; 
}

void averageTemp(void)
{
    tempArray[index] = temp;
    if(index == 9)
    {
        sum = 0;
        avgTempCalculated = 1; // This means that the new avg temp is calculated and ready to be used
        for(index = 0; index < SIZE; index++)
        {
            sum += tempArray[index];
        }
        avgTemp = sum / SIZE;
    }
    index = (index + 1) % 10;
}

void temperatureSense(void)
{
    if(senseTempFlag)
    {
        senseTempFlag = 0;
        ADC_Read();
        Digital2Temp(digitalValue);
        averageTemp();
    }
}