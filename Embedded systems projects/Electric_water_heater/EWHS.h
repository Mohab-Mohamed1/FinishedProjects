/* 
 * File:   EWHS.h
 * Author: Mohab
 *
 * Created on July 12, 2020, 7:21 PM
 */

#ifndef EWHS_H
#define	EWHS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

/******************************************************************************
                               Function prototypes
 ******************************************************************************/

void EWHS_Init(void);
void On_Off_SwitchInit(void);
void EWHS_Off(void);
void EWHS_On(void);
void EWHS(void);

/******************************************************************************
                               Variables 
 ******************************************************************************/

extern unsigned char state;
extern unsigned char OnState;
extern unsigned char OffState;

#endif	/* EWHS_H */

