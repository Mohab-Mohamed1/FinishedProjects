/* 
 * File:   I2C_EEPROM2.h
 * Author: Mohab
 *
 * Created on July 18, 2020, 1:09 PM
 */

#ifndef I2C_EEPROM2_H
#define	I2C_EEPROM2_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

//---[ I2C Routines ]---

void I2C_Master_Init(const unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_ACK();
void I2C_NACK();
unsigned char I2C_Master_Write(unsigned char);
unsigned char I2C_Read_Byte(void);


//---[ EEPROM Routines ]---

void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len);
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len);
void temp2Str2(void);
void retreiveTemp2(void);
void saveTemp2(void);


#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0
#define DATA_LOCATION 0x00


extern unsigned char str[2];



#endif	/* I2C_EEPROM2_H */

