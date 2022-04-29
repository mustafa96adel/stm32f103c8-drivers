#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "stm32f103xx.h"
#include "UART1_interface.h"

u8 UART1_u8Init(UART1_config_t* Copy_PUART1_config_tToConfig)
{
	SET_BIT(UART1->CR1, 13);
	switch (Copy_PUART1_config_tToConfig->wordLength)
	{
	case UART1_u8_8DATA_BITS_WORD :
		SET_BIT(UART1->CR1, 12);
		break;
	case UART1_u8_9DATA_BITS_WORD :
		CLR_BIT(UART1->CR1, 12);
		break;
	default :
		return STD_TYPES_NOK;
	}

	if (Copy_PUART1_config_tToConfig->baudRate & 0xffff0000)
		return STD_TYPES_NOK;
	UART1->BRR = Copy_PUART1_config_tToConfig->baudRate;

	if (Copy_PUART1_config_tToConfig->transmitReceive > 3) return STD_TYPES_NOK;
	UART1->CR1 &= ~(0x0000000c);
	UART1->CR1 += (Copy_PUART1_config_tToConfig->transmitReceive << 2);

	return STD_TYPES_OK;
}

u8 UART1_u8SendWord(u16 Copy_u16Word)
{
	if (Copy_u16Word & 0xfffffe00) return STD_TYPES_NOK;
	UART1->DR = Copy_u16Word;
	while (!GET_BIT(UART1->SR, 7));
	while(!GET_BIT(UART1 -> SR, 6));
	return STD_TYPES_OK;
}

u8 UART1_u8ReceiveWord(u8* Copy_Pu16Word)
{
	if (Copy_Pu16Word == NULL) return STD_TYPES_NOK;
	if (!GET_BIT(UART1->SR, 5)) {*Copy_Pu16Word = 0; return STD_TYPES_NOK;}
	*Copy_Pu16Word = UART1->DR;
	CLR_BIT(UART1->SR, 5);
	return STD_TYPES_OK;
}
