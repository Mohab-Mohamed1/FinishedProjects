/* 
 * File:   TempSetMode.h
 * Author: Mohab
 *
 * Created on July 7, 2020, 11:37 AM
 */

#ifndef TEMPSETMODE_H
#define	TEMPSETMODE_H

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

void buttonsInit(void);
void tempSetMode(void);
void SetTemp(void);

/******************************************************************************
                               Variables 
 ******************************************************************************/

extern unsigned char upPrevState;
extern unsigned char upCurrState;
extern unsigned char downPrevState;
extern unsigned char downCurrState;
extern unsigned char targetTemp;
extern unsigned char display_OFF;
extern unsigned char E2PROM_flag;

#endif	/* TEMPSETMODE_H */

