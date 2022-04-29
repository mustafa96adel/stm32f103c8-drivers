#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "stm32f103xx.h"
#include "EXTI_interface.h"

/**************************************** Important typedefs ****************************************/

typedef void(*fptr)(void);

/**************************************** Important variables ****************************************/

static fptr Global_pfArray[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

u8 EXTI_u8SetInterruptStatus(u8 Copy_u8LineNumber, u8 Copy_u8Status)
{
	if (Copy_u8LineNumber > 15) return STD_TYPES_NOK;
	switch (Copy_u8Status)
	{
	case ENABLE:
		SET_BIT(EXTI->IMR, Copy_u8LineNumber);
		break;
	case DISABLE:
		CLR_BIT(EXTI->IMR, Copy_u8LineNumber);
		break;
	default :
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

u8 EXTI_u8SetInterruptEdge(u8 Copy_u8LineNumber, u8 Copy_u8Edge)
{
	if (Copy_u8LineNumber > 15) return STD_TYPES_NOK;
	switch (Copy_u8Edge)
	{
	case EXTI_u8_RISING_EDGE:
		SET_BIT(EXTI->RTSR, Copy_u8LineNumber);
		break;
	case EXTI_u8_FALLING_EDGE:
		SET_BIT(EXTI->FTSR, Copy_u8LineNumber);
		break;
	default :
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

u8 EXTI_u8ClearInterruptPending(u8 Copy_u8LineNumber)
{
	if (Copy_u8LineNumber > 15) return STD_TYPES_NOK;
	SET_BIT(EXTI->PR, Copy_u8LineNumber);
	return STD_TYPES_OK;
}

u8 EXTI_u8SetInterruptCallback(u8 Copy_u8EXTINumber, void (*Copy_pfCallback)(void))
{

	if (Copy_u8EXTINumber > 15 || Copy_pfCallback == NULL) return STD_TYPES_NOK;
	if (Copy_u8EXTINumber > 4 && Copy_u8EXTINumber < 10)
	{
		Copy_u8EXTINumber = 5;
	}
	else if (Copy_u8EXTINumber >= 10)
	{
		Copy_u8EXTINumber = 6;
	}

	Global_pfArray[Copy_u8EXTINumber] = Copy_pfCallback;

	return STD_TYPES_OK;
}


/**************************************** EXTI ISRs ****************************************/

void EXTI0_IRQHandler(void)
{
	SET_BIT(EXTI->PR, 0);

	if (Global_pfArray[EXTI_LINE0] != NULL)
	{
		Global_pfArray[EXTI_LINE0]();
	}
}

void EXTI1_IRQHandler(void)
{
	SET_BIT(EXTI->PR, 1);

	if (Global_pfArray[EXTI_LINE1] != NULL)
	{
		Global_pfArray[EXTI_LINE1]();
	}
}

void EXTI2_IRQHandler(void)
{
	SET_BIT(EXTI->PR, 2);

	if (Global_pfArray[EXTI_LINE2] != NULL)
	{
		Global_pfArray[EXTI_LINE2]();
	}

}

void EXTI3_IRQHandler(void)
{
	SET_BIT(EXTI->PR, 3);

	if (Global_pfArray[EXTI_LINE3] != NULL)
	{
		Global_pfArray[EXTI_LINE3]();
	}
}

void EXTI4_IRQHandler(void)
{
	SET_BIT(EXTI->PR, 4);

	if (Global_pfArray[EXTI_LINE4] != NULL)
	{
		Global_pfArray[EXTI_LINE4]();
	}
}

void EXTI9_5_IRQHandler(void)
{
	EXTI->PR |= (0b11111 << 5);

	if (Global_pfArray[EXTI_LINE5_9] != NULL)
	{
		Global_pfArray[EXTI_LINE5_9]();
	}
}

void EXTI15_10_IRQHandler(void)
{
	EXTI->PR |= (0b111111 << 10);

	if (Global_pfArray[EXTI_LINE10_15] != NULL)
	{
		Global_pfArray[EXTI_LINE10_15]();
	}
}
