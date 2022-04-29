/**************************************** Includes ****************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
#include "NVIC_interface.h"

/**************************************** Functions' definitions ****************************************/

u8 NVIC_u8EnableInterrupt(u8 Copy_u8InterruptNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_u8InterruptNumber <= 31)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		SET_BIT(NVIC -> ISER[0], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 32 && Copy_u8InterruptNumber <= 63)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 32;
		SET_BIT(NVIC -> ISER[1], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 64 && Copy_u8InterruptNumber <= 95)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 64;
		SET_BIT(NVIC -> ISER[2], Copy_u8InterruptNumber);
	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

u8 NVIC_u8DisableInterrupt(u8 Copy_u8InterruptNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_u8InterruptNumber <= 31)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		SET_BIT(NVIC -> ICER[0], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 32 && Copy_u8InterruptNumber <= 63)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 32;
		SET_BIT(NVIC -> ICER[1], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 64 && Copy_u8InterruptNumber <= 95)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 64;
		SET_BIT(NVIC -> ICER[2], Copy_u8InterruptNumber);
	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

u8 NVIC_u8SetInterruptPending(u8 Copy_u8InterruptNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_u8InterruptNumber <= 31)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		SET_BIT(NVIC -> ISPR[0], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 32 && Copy_u8InterruptNumber <= 63)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 32;
		SET_BIT(NVIC -> ISPR[1], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 64 && Copy_u8InterruptNumber <= 95)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 64;
		SET_BIT(NVIC -> ISPR[2], Copy_u8InterruptNumber);
	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

u8 NVIC_u8ClearInterruptPending(u8 Copy_u8InterruptNumber)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_u8InterruptNumber <= 31)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		SET_BIT(NVIC -> ICPR[0], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 32 && Copy_u8InterruptNumber <= 63)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 32;
		SET_BIT(NVIC -> ICPR[1], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 64 && Copy_u8InterruptNumber <= 95)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 64;
		SET_BIT(NVIC -> ICPR[2], Copy_u8InterruptNumber);
	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

u8 NVIC_u8InterruptIsActive(u8 Copy_u8InterruptNumber, u8* Copy_pu8InterruptStatus)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;

	if(Copy_u8InterruptNumber <= 31)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		*Copy_pu8InterruptStatus = GET_BIT(NVIC -> IABR[0], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 32 && Copy_u8InterruptNumber <= 63)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 32;
		*Copy_pu8InterruptStatus = GET_BIT(NVIC -> IABR[1], Copy_u8InterruptNumber);
	}
	else if(Copy_u8InterruptNumber >= 64 && Copy_u8InterruptNumber <= 95)
	{
		Local_u8ErrorState = STD_TYPES_OK;
		Copy_u8InterruptNumber -= 64;
		*Copy_pu8InterruptStatus = GET_BIT(NVIC -> IABR[2], Copy_u8InterruptNumber);
	}
	else
	{
		/*Do nothing*/
	}

	return Local_u8ErrorState;
}

u8 NVIC_u8SetGroupPriority(u8 Copy_u8InterruptNumber, u8 Copy_u8GroupPriority)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	u8 Local_u8RegisterNumber = Copy_u8InterruptNumber / 4;
	u8 Local_u8InterruptByte = Copy_u8InterruptNumber % 4;

	SCB_AIRCR = 0x05FA0300;

	NVIC -> IPR[Local_u8RegisterNumber] &= ~(0b1111 << ((8 * Local_u8InterruptByte) + 4));
	NVIC -> IPR[Local_u8RegisterNumber] |= (Copy_u8GroupPriority << ((8 * Local_u8InterruptByte) + 4));
	return Local_u8ErrorState;
}
