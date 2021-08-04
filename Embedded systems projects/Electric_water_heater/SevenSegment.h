/* 
 * File:   SevenSegment.h
 * Author: Mohab
 *
 * Created on July 9, 2020, 12:02 AM
 */

#ifndef SEVENSEGMENT_H
#define	SEVENSEGMENT_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

/******************************************************************************
                               Macros 
 ******************************************************************************/


#define SIZE 10

/******************************************************************************
                               Function prototypes
 ******************************************************************************/

void sevenSegmentInit(void);
void setDisplay(unsigned char);
void sevenSegmentOFF(void);

/******************************************************************************
                               Variables 
 ******************************************************************************/

extern unsigned char segmentNumbers[SIZE];

#endif	/* SEVENSEGMENT_H */

