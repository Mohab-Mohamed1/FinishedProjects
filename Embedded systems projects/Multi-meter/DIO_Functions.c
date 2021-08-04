#include "stdtypes.h"

#include "DIO_Interface.h"


// fuction to intialize all dio control registers with zero to clear any previous data.
void DIO_voidInitialize(void)
{
	u8 i;
	u8 volatile *reg = PIND;
	for(i = PORT_D; i <= PORT_A; i++)
	{
		reg = PIND + (ADDR_OFFSET * i);
		*reg = 0x00;
	}
	reg = DDRD;
	for(i = PORT_D; i <= PORT_A; i++)
	{
		reg = DDRD + (ADDR_OFFSET * i);
		*reg = 0x00;
	}
	reg = PORTD;
	for(i = PORT_D; i <= PORT_A; i++)
	{
		reg = PORTD + (ADDR_OFFSET * i);
		*reg = 0x00;
	}
}

// Function that sets the pin to be output or input
STD_ERROR DIO_SetPinDir(u8 port_, u8 pin_, u8 dir_)
{
	u8 volatile *reg = DDRD;
	STD_ERROR lock_error = OK;
	if(pin_>= P_0 && pin_<= P_7)
	{
		if(port_ >= PORT_D && port_ <= PORT_A)
		{
			reg = DDRD + (ADDR_OFFSET * port_);
			if(dir_ == PIN_DIR_OUTPUT)
			{
				*reg |= (SHFT_OP << pin_);
			}
			else if(dir_ == PIN_DIR_INPUT)
			{
				*reg &= ~(SHFT_OP << pin_);
			}
			else
			{
				lock_error = NOT_OK;
			}
		}
		else
		{
			lock_error = NOT_OK;
		}
	}

	return lock_error;
}

//Function that sets the pins to output 5v or 0v.
STD_ERROR DIO_SetPinValue(u8 port_, u8 pin_,  u8 value_)
{
	u8 volatile *reg = PORTD;
	STD_ERROR lock_error = OK;
	if(pin_>= P_0 && pin_<= P_7)
	{
		if(port_ >= PORT_D && port_ <= PORT_A)
		{
			reg = PORTD + (ADDR_OFFSET * port_);
			if(value_ == PIN_VAL_HIGH)
			{
				*reg |= (SHFT_OP << pin_);
			}
			else
				if(value_ == PIN_VAL_LOW)
				{
					*reg &= ~(SHFT_OP << pin_);
				}
				else
				{
					lock_error = NOT_OK;
				}
		}
		else
		{
			lock_error = NOT_OK;
		}
	}
	return lock_error;
}

STD_ERROR DIO_SetPortDir(u8 port_, u8 dir_)
{
	u8 volatile *reg = DDRD;
	STD_ERROR lock_error = OK;
	if(port_ >= PORT_D && port_ <= PORT_A)
	{
		if(dir_ >= 0x00 && dir_ <= 0xFF)
		{
			reg = DDRD + (ADDR_OFFSET * port_);
			*reg = dir_;
		}
		else
		{
			lock_error = NOT_OK;
		}
	}
	else
	{
		lock_error = NOT_OK;
	}
	return lock_error;
}

STD_ERROR DIO_SetPortValue(u8 port_, u8 val_)
{
	u8 volatile *reg = PORTD;
	STD_ERROR lock_error = OK;
	if(port_ >= PORT_D && port_ <= PORT_A)
	{

		if(val_ >= 0x00 && val_ <= 0xFF)
		{
			reg = PORTD + (ADDR_OFFSET * port_);
			*reg = val_;
		}
		else
		{
			lock_error = NOT_OK;
		}
	}
	else
	{
		lock_error = NOT_OK;
	}
	return lock_error;
}


// Fuction to get the status of a pin
STD_ERROR DIO_GetPinValue(u8 port_, u8 pin_, u8* val_)
{
	u8 volatile *reg = PIND;
	STD_ERROR lock_error = OK;
	if(pin_ >= P_0 && pin_ <= P_7)
	{
		if(port_ >= PORT_D && port_ <= PORT_A)
		{
			reg = PIND + (ADDR_OFFSET * port_);
			*val_ = ((*reg) & (SHFT_OP << pin_)) >> (pin_);
		}
	}
	else
	{
		lock_error = NOT_OK;
	}
	return lock_error;
}










