/*
 * Multimeter.h
 *
 * Created: 12/22/2020 12:06:56 PM
 *  Author: Mohab
 */  


#ifndef MULTIMETER_H_
#define MULTIMETER_H_


/*
Input:
Output: 
Description:
*/

/*
Input: None
Output: None
Description: Initializes the ADC and UART peripheral
*/
void SystemInit(void);

/*
Input: None
Output: None
Description: Wait for a valid frame the request change in the operation mode then perform the change.
*/
void OpModeChange(void);

/*
Input: None
Output: None
Description: Sends the voltage data frame to the pc through UART
*/
void SendvDF(void);


/*
Input: None
Output: None
Description: Sends the current data frame to the pc through UART
*/
void SendcDF(void);

/*
Input: None
Output: None
Description: Sends the resistance data frame to the pc through UART
*/
void SendrDF(void);


#endif /* MULTIMETER_H_ */