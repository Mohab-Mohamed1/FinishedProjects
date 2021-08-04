/* 
 * File:   ADC.h
 * Author: Mohab
 *
 * Created on July 4, 2020, 9:59 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


/******************************************************************************
                                Macros
 ******************************************************************************/
#define SIZE  10

/******************************************************************************
                               Function prototypes
 ******************************************************************************/
void ADC_Init(void);
void ADC_Read(void);
void ADC_On(void);
void ADC_Off(void);
void Digital2Temp(unsigned int);
void averageTemp(void);
void temperatureSense(void);

/******************************************************************************
                               Variables 
 ******************************************************************************/

extern float digitalValue;
extern unsigned char temp;
extern unsigned char tempArray[SIZE];
extern unsigned char index;
extern unsigned char avgTempCalculated;
unsigned char senseTempFlag;
extern char avgTemp;
extern unsigned int sum;

#endif	/* ADC_H */

