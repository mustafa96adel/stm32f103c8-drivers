#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "stm32f103xx.h"
#include "DMA_interface.h"

typedef void(*fptr_t)(void);
static fptr_t DMA_Afptr[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

u8 DMA_u8Init(DMA_Config_t* Copy_DMA_Config_tToConfigure)
{
	/* Circular Mode */
	switch (Copy_DMA_Config_tToConfigure->circularMode)
	{
	case ENABLE :
		SET_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 5);
		break;
	case DISABLE:
		CLR_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 5);
		break;
	default:
		return STD_TYPES_NOK;
	}

	/* Number of data units */
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CNDTR = Copy_DMA_Config_tToConfigure->numberOfDataUnits;

	/* Priority Level */
	if (Copy_DMA_Config_tToConfigure->priorityLevel > 3) return STD_TYPES_NOK;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x00003000);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_DMA_Config_tToConfigure->priorityLevel << 12);
	return STD_TYPES_OK;
}

u8 DMA_u8EnableInterrupts(DMA_Config_t* Copy_DMA_Config_tToConfigure, u8 Copy_u8InterruptType)
{
	if (Copy_u8InterruptType > 6) return STD_TYPES_NOK;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x0000000E);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_u8InterruptType << 1);
	return STD_TYPES_OK;
}

u8 DMA_u8TransferBetweenMemAndMem(DMA_Config_t* Copy_DMA_Config_tToConfigure, u32 Copy_u32SourceAddress, u32 Copy_u32DestinationAddress, u32 Copy_u8SourceSize, u32 Copy_u8DestinationSize)
{
	if (Copy_DMA_Config_tToConfigure->channelNumber > 6) return STD_TYPES_NOK;
	CLR_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 4);
	SET_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 14);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CPAR = Copy_u32SourceAddress;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CMAR = Copy_u32DestinationAddress;

	if (Copy_u8DestinationSize > 2 || Copy_u8SourceSize > 2) return STD_TYPES_NOK;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x00000300);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x00000c00);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_u8SourceSize << 8);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_u8SourceSize << 10);

	return STD_TYPES_OK;
}

u8 DMA_u8TransferBetweenMemAndPeriph(DMA_Config_t* Copy_DMA_Config_tToConfigure, u32 Copy_u32MemAddress, u32 Copy_u32PeriphAddress, u8 Copy_u8MemSize, u8 Copy_u8PeriphSize, u8 Copy_u8Direction)
{
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CPAR = Copy_u32PeriphAddress;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CMAR = Copy_u32MemAddress;

	switch (Copy_u8Direction)
	{
	case DMA_u8_PERIPH_TO_MEM_DIRECTION :
		CLR_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 4);
		break;
	case DMA_u8_MEM_TO_PERIPH_DIRECTION :
		SET_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 4);
		break;
	default :
		return STD_TYPES_NOK;
	}
	if (Copy_u8MemSize > 2 || Copy_u8PeriphSize > 2) return STD_TYPES_NOK;
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x00000300);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR &= ~(0x00000c00);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_u8PeriphSize << 8);
	DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR |= (Copy_u8MemSize << 10);
	return STD_TYPES_OK;
}

u8 DMA_u8SetCallBackFunction(DMA_Config_t* Copy_DMA_Config_tToConfigure, void (*Copy_pf)(void))
{
	if (Copy_pf == NULL) return STD_TYPES_NOK;
	DMA_Afptr[Copy_DMA_Config_tToConfigure->channelNumber] = Copy_pf;
	return STD_TYPES_OK;
}

u8 DMA_u8EnDisDMA(DMA_Config_t* Copy_DMA_Config_tToConfigure,u8 Copy_u8EnDis)
{
	switch (Copy_u8EnDis)
	{
	case ENABLE:
		SET_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 0);
		break;
	case DISABLE:
		CLR_BIT(DMA->Reg[Copy_DMA_Config_tToConfigure->channelNumber].CCR, 0);
		break;
	default:
		return STD_TYPES_NOK;
	}
	return STD_TYPES_OK;
}

void DMA1_Channel1_IRQHandler(void)
{
	/*Clearing the TC flag*/
	SET_BIT(DMA->IFCR, 1);

	if (DMA_Afptr[0] != NULL)
	{
		DMA_Afptr[0]();
	}
	CLR_BIT(DMA->Reg[0].CCR, 0);
}
