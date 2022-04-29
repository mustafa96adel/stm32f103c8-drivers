#include "STD_TYPES.h"
#include "stm32f103xx.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

u8 GPIO_u8PinInit(GPIO_Pin* Copy_StrPin)
{
	u8 Local_u8Temp = Copy_StrPin->pinMode;
	if (Copy_StrPin->pinNumber > 15 || Copy_StrPin->port > 5 || Copy_StrPin->pinMode > 17)
			return STD_TYPES_NOK;
	if (Copy_StrPin->pinMode > 15)
	{
		if (Copy_StrPin->pinMode & 1)
			SET_BIT(GPIO[Copy_StrPin->port].ODR, Copy_StrPin->pinNumber);
		else
			CLR_BIT(GPIO[Copy_StrPin->port].ODR, Copy_StrPin->pinNumber);
		Copy_StrPin->pinMode >>= 1;
	}
	if ( Copy_StrPin->pinNumber < 8)
	{
		GPIO[Copy_StrPin->port].CRL &= ~((u32)0xF << (Copy_StrPin->pinNumber << 2));
		GPIO[Copy_StrPin->port].CRL |= (Copy_StrPin->pinMode << ((Copy_StrPin->pinNumber << 2)));
	}
	else if (Copy_StrPin->pinMode < 16)
	{
		GPIO[Copy_StrPin->port].CRH &= ~(0xF << ((Copy_StrPin->pinNumber - 8) << 2));
		GPIO[Copy_StrPin->port].CRH |= (Copy_StrPin->pinMode << (((Copy_StrPin->pinNumber - 8) << 2)));
	}
	Copy_StrPin->pinMode = Local_u8Temp;
	return STD_TYPES_OK;
}

u8 GPIO_u8SetPinOutput(GPIO_Pin* Copy_StrPin, u8 Copy_u8PinValue)
{
	switch(Copy_u8PinValue)
	{
		case GPIO_u8_LOW :
			CLR_BIT(GPIO[Copy_StrPin->port].ODR, Copy_StrPin->pinNumber);
			break;
		case GPIO_u8_HIGH :
			SET_BIT(GPIO[Copy_StrPin->port].ODR, Copy_StrPin->pinNumber);
			break;
		default :
			return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

u8 GPIO_u8GetPinInput(GPIO_Pin* Copy_StrPin)
{
	return GET_BIT(GPIO[Copy_StrPin->port].IDR, Copy_StrPin->pinNumber);
}

u8 GPIO_u8SetPortOutput(u8 Copy_u8Port, u8 Copy_u8PortValue)
{
	if (Copy_u8Port > GPIO_u8_PORT_F || Copy_u8PortValue > 0xFFFF)
		return STD_TYPES_NOK;
	GPIO[Copy_u8Port].ODR = Copy_u8PortValue;
	return STD_TYPES_OK;
}

u16 GPIO_u8GetPortInput(u8 Copy_u8Port)
{
	return GPIO[Copy_u8Port].IDR;
}

u8 GPIO_u8TogglePin(GPIO_Pin* Copy_StrPin)
{
	if (Copy_StrPin->pinNumber > 15 || Copy_StrPin->port > 5)
			return STD_TYPES_NOK;
	TOG_BIT(GPIO[Copy_StrPin->port].ODR, Copy_StrPin->pinNumber);
	return STD_TYPES_OK;
}
