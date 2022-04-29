#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"
#include "SYSTICK_interface.h"

u8 static SSTK_u8SingleInterval;
static void (*SSTK_pf)(void);
u8 SSTK_u8AHBMode(u8 Copy_u8AHBDiv)
{
	switch (Copy_u8AHBDiv)
	{
	case SSTK_u8_AHB_NO_DIV:
		SET_BIT(SSTK->CTRL, 2);
		break;
	case SSTK_u8_AHB_DIV_BY_8 :
		CLR_BIT(SSTK->CTRL, 2);
		break;
	default: return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

u8 SSTK_u8SetBusyWait(u32 Copy_u32NumOfTicks)
{
	if ((Copy_u32NumOfTicks & 0xff000000) != 0) return STD_TYPES_NOK;
	SSTK->RELOAD = Copy_u32NumOfTicks;
	SSTK->CURRENT = 0;
	SSTK_voidRun();
	while (!GET_BIT(SSTK->CTRL, 16));
	SSTK_voidStop();
	return STD_TYPES_OK;
}


void 	SSTK_voidRun				(void)	{SET_BIT(SSTK->CTRL, 0);}

void	SSTK_voidStop				(void)	{CLR_BIT(SSTK->CTRL, 0); SSTK->CURRENT = 0;}

void	SSTK_voidPause				(void)	{CLR_BIT(SSTK->CTRL, 0);}

void 	SSTK_voidEnableInterrupts	(void)	{SET_BIT(SSTK->CTRL, 1);}

void 	SSTK_voidDisableInterrupts  (void)	{CLR_BIT(SSTK->CTRL, 1);}

u32 	SSTK_u32ElapsedTime			(void)	{return SSTK->RELOAD - SSTK->CURRENT;}

u32 	SSTK_u32RemainingTime		(void)	{return SSTK->CURRENT;}

u8 SSTK_u8SetIntervalSingle(u32 Copy_u32NumOfTicks)
{
	if ((Copy_u32NumOfTicks & 0xff000000) != 0) return STD_TYPES_NOK;
	SSTK_u8SingleInterval = 1;
	SSTK_voidEnableInterrupts();
	SSTK->RELOAD = Copy_u32NumOfTicks;
	SSTK->CURRENT = 0;
	SSTK_voidRun();
	return STD_TYPES_OK;
}

u8 SSTK_u8SetIntervalPeriodic(u32 Copy_u32NumOfTicks)
{
	if ((Copy_u32NumOfTicks & 0xff000000) != 0) return STD_TYPES_NOK;
	SSTK_u8SingleInterval = 0;
	SSTK_voidEnableInterrupts();
	SSTK->RELOAD = Copy_u32NumOfTicks - 1;
	SSTK->CURRENT = 0;
	SSTK_voidRun();
	return STD_TYPES_OK;
}
void	SSTK_voidSetCallBackFunction(void (*Copy_pf)(void))
{
	SSTK_pf = Copy_pf;
}
void SysTick_Handler(void)
{
	u8 Local_u8Temp;
	if (SSTK_u8SingleInterval)
	{
		SSTK_voidDisableInterrupts();
		SSTK_voidStop();
	}
	if (SSTK_pf != NULL)
		SSTK_pf();
	Local_u8Temp = SSTK->CTRL;
}

u8 SSTK_u8SetRELOADReg(u32 Copy_u32LoadValue)
{
	if (Copy_u32LoadValue & 0xff000000) return STD_TYPES_NOK;
	SSTK->RELOAD = Copy_u32LoadValue;
	SSTK->CURRENT = 0;
	return STD_TYPES_OK;
}
