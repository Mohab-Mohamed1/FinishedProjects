#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_



#define PIND (u8 volatile*) 0x30
#define DDRD (u8 volatile*) 0x31
#define PORTD (u8 volatile*) 0x32

#define ZERO         0
#define SHFT_OP (u8) 1
#define ADDR_OFFSET  (u8) 3
// MCU Pins
#define P_0 (u8) 0
#define P_1 (u8) 1
#define P_2 (u8) 2
#define P_3 (u8) 3
#define P_4 (u8) 4
#define P_5 (u8) 5
#define P_6 (u8) 6
#define P_7 (u8) 7
// MCU Ports
#define PORT_A (u8) 3
#define PORT_B (u8) 2
#define PORT_C (u8) 1
#define PORT_D (u8) 0

// Functions Prototypes

void DIO_voidInitialize(void);
STD_ERROR DIO_SetPinValue(u8 port_, u8 pin_,  u8 value_);
STD_ERROR DIO_SetPinDir(u8 port_,u8 pin_,u8 dir_);
STD_ERROR DIO_SetPortDir(u8 port_, u8 dir_);
STD_ERROR DIO_SetPortValue(u8 port_, u8 value);
STD_ERROR DIO_GetPinValue(u8 port_, u8 pin_, u8* value_);





//DDR_PIN_Direction
#define PIN_DIR_OUTPUT (u8) 100
#define PIN_DIR_INPUT (u8)  10
//PORT_PIN_VALUE
#define PIN_VAL_HIGH (u8) 1
#define PIN_VAL_LOW       0
//Port_direction
#define PORT_DIR_ALL_OP (u8)         0XFF
#define PORT_DIR_ALL_INP (u8)        0X00
#define PORT_DIR_HLF_OP_HLF_INP (u8) 0XF0
#define PORT_DIR_HLF_INP_HLF_OP (u8) 0X0F
//Port_value
#define PORT_VAL_ALL_H (u8)         0XFF
#define PORT_VAL_ALL_L (u8)        0X00
#define PORT_VAL_HLF_H_HLF_L (u8) 0XF0
#define PORT_VAL_HLF_L_HLF_H (u8) 0X0F







#endif /* DIO_INTERFACE_H_ */
