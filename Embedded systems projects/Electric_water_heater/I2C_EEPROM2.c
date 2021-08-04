#include "config.h"
#include "I2C_EEPROM2.h"
#include "TempSetMode.h"




unsigned char str[2];
unsigned char E2PROM_flag;

void I2C_Master_Init(const unsigned long baud )
{
  SSPCON = 0x28;
  SSPCON2 = 0x00;
  SSPSTAT = 0x00;
  SSPADD = ((_XTAL_FREQ/4)/baud) - 1;
  TRISC3 = 1;
  TRISC4 = 1;
}


void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}


void I2C_Master_Start()
{
  I2C_Master_Wait();
  SEN = 1;
}


void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;
}


void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;
}


void I2C_ACK(void)
{
  ACKDT = 0; // 0 -> ACK
  I2C_Master_Wait();
  ACKEN = 1; // Send ACK
}


unsigned char I2C_Master_Write(unsigned char data)
{
  I2C_Master_Wait();
  SSPBUF = data;
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0;
  return ACKSTAT;
}


unsigned char I2C_Read_Byte(void)
{
  //---[ Receive & Return A Byte ]---
  I2C_Master_Wait();
  RCEN = 1; // Enable & Start Reception
  while(!SSPIF); // Wait Until Completion
  SSPIF = 0; // Clear The Interrupt Flag Bit
  I2C_Master_Wait();
  return SSPBUF; // Return The Received Byte
}


void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add);
  I2C_Master_Wait();
  for(unsigned int i=0; i<len; i++)
  {
     I2C_Master_Write(data[i]);
     I2C_Master_Wait();
  }
    
  
  I2C_Master_Stop();
}


void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len)
{
    unsigned char byte;
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  
  I2C_Master_Write(add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
 /*for(unsigned int i=0; i<len; i++)
  {
    data[i] = I2C_Read_Byte();
    I2C_ACK();
  }*/
    
    byte = I2C_Read_Byte();
    if(byte >= 0x33 && byte <= 0x37)
    {
        data[0] = byte;
    }
    else
    {
        data[0] = 0x36;
    }
    I2C_ACK();
    
    byte = I2C_Read_Byte();
    if(byte >= 0x30 && byte <= 0x39)
    {
        data[1] = byte;
    }
    else
    {
        data[1] = 0x30;
    }
    I2C_ACK();
    
  I2C_Master_Stop();
}



void temp2Str2(void)
{
    str[0] = (targetTemp / 10) + 0x30; // first digit (Tenth)
    str[1] = (targetTemp % 10) + 0x30; // second digit (unit)
}


void retreiveTemp2(void)
{
    EEPROM_Read_Page(DATA_LOCATION, str, 2);
    targetTemp = (str[0] - 0x30) * 10 + (str[1] - 0x30); 
}


void saveTemp2(void)
{
   
    temp2Str2();
    EEPROM_Write_Page(DATA_LOCATION, str, 2);
    
}