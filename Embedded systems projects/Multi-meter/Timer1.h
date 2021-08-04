/*
 * Timer1.h
 *
 * Created: 12/23/2020 11:24:24 PM
 *  Author: Mohab
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

extern volatile uint8_t ovfCounter;
extern volatile uint8_t sendFlag;

void timerInit(void);

#endif /* TIMER1_H_ */