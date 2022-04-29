/***********************************************************************/
/*************** Name 	 : Mustafa Adel	 *******************************/
/*************** Date 	 : 5 / 7 / 2021	 *******************************/
/*************** Version : 1.0           *******************************/
/*************** SWC     : RCC			 *******************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "stm32f103xx.h"
#include "RCC_private.h"
#include "RCC_interface.h"

void RCC_u8EnableHSE()
{
	SET_BIT(RCC->CR,16);
	SET_BIT(RCC->CFGR,0);
	CLR_BIT(RCC->CFGR,1);
}

void RCC_u8EnableHSI()
{
	SET_BIT(RCC->CR,0);
	CLR_BIT(RCC->CFGR,0);
	CLR_BIT(RCC->CFGR,1);
}

u8 RCC_u8enablePll(u8 Copy_u8MulFactor, u8 Copy_u8PLLSource)
{
	Copy_u8MulFactor -= 2;
	if (Copy_u8MulFactor > 13)
		return STD_TYPES_NOK;							//The "Copy_u8MulFactor" has exceeded the limit
	switch(Copy_u8PLLSource)
	{
	case RCC_u8_PLL_SOURCE_HSI_DIVIDED_BY_2:
		CLR_BIT(RCC->CFGR, 16);
		RCC_u8EnableHSI();
		break;
	case RCC_u8_PLL_SOURCE_HSE:
		SET_BIT(RCC->CFGR, 16);
		RCC_u8EnableHSE();
		break;
	default :
		return STD_TYPES_NOK;
	}

	CLR_BIT(RCC->CR, 24);
	RCC->CFGR &= 0xFFC3FFFF;
	RCC->CFGR |= Copy_u8MulFactor << 18;

	SET_BIT(RCC->CR, 24);
	SET_BIT(RCC->CFGR, 1);
	CLR_BIT(RCC->CFGR, 0);
	return STD_TYPES_OK;
}

u8 RCC_u8SetMCO(u8 Copy_u8Source)
{
	if (Copy_u8Source > 7)
		return STD_TYPES_NOK;
	RCC->CFGR &= ~(7 << 24);
	RCC->CFGR |= (Copy_u8Source << 24);
	return STD_TYPES_OK;
}
u8 RCC_u8EnablePeripheralClk(u8 Copy_u8PeripheralID)
{
	u8 Local_u8BitNumber = Copy_u8PeripheralID & 0x1F;
	u8 Local_u8RegNumber = Copy_u8PeripheralID >> 5;
	if (Copy_u8PeripheralID > 93)
		return STD_TYPES_NOK;
	SET_BIT(RCC_Au32_PERIPHERALS[Local_u8RegNumber], Local_u8BitNumber);
	return STD_TYPES_OK;
}

u8 RCC_u8DisablePeripheralClk(u8 Copy_u8PeripheralID)
{
	if (Copy_u8PeripheralID > 93)
		return STD_TYPES_NOK;
	CLR_BIT(RCC_Au32_PERIPHERALS[Copy_u8PeripheralID >> 5], Copy_u8PeripheralID & 0x0000001F);
	return STD_TYPES_OK;
}
