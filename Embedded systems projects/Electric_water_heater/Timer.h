/* 
 * File:   Timer0.h
 * Author: Mohab
 *
 * Created on July 6, 2020, 5:54 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

/******************************************************************************
                               Macros & Directives
 ******************************************************************************/


/******************************************************************************
                               Function prototypes
 ******************************************************************************/

void Timers_Init(void);
void Timer0_Restart(void);

void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_Restart(void);

void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_Restart(void);

__interrupt() void ISR();


/******************************************************************************
                               Variables 
 ******************************************************************************/

extern unsigned char checkTemp;
extern unsigned char T0_ovfCounter;
extern unsigned char T1_ovfCounter;
extern unsigned int T2_ovfCounter;

#endif	/* TIMER0_H */

