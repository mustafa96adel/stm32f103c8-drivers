#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

#define DMA_u8_CHANNEL1												0
#define DMA_u8_CHANNEL2												1
#define DMA_u8_CHANNEL3												2
#define DMA_u8_CHANNEL4												3
#define DMA_u8_CHANNEL5												4
#define DMA_u8_CHANNEL6												5
#define DMA_u8_CHANNEL7												6

#define DMA_u8_LOW_PRIORITY											0
#define DMA_u8_MED_PRIORITY											1
#define DMA_u8_HIGH_PRIORITY										2
#define DMA_u8_VERY_HIGH_PRIORITY									3

typedef struct
{
	u8 channelNumber;
	u8 priorityLevel;
	u16 numberOfDataUnits;
	u8 circularMode;
}DMA_Config_t;
u8 DMA_u8Init(DMA_Config_t* Copy_DMA_Config_tToConfigure);

#define DMA_u8_TRANSFER_COMPLETE_INTERRUPT							0b001
#define DMA_u8_HALF_TRANSFER_INTERRUPT								0b010
#define DMA_u8_TRANSFER_ERROR_INTERRUPT								0b100
u8 DMA_u8EnableInterrupts(DMA_Config_t* Copy_DMA_Config_tToConfigure, u8 Copy_u8InterruptType);

#define DMA_u8_8BIT_SIZE											0
#define DMA_u8_16BIT_SIZE											1
#define DMA_u8_32BIT_SIZE											2
u8 DMA_u8TransferBetweenMemAndMem(DMA_Config_t* Copy_DMA_Config_tToConfigure, u32 Copy_u32SourceAddress, u32 Copy_u32DestinationAddress, u32 Copy_u8SourceSize, u32 Copy_u8DestinationSize);

#define	DMA_u8_PERIPH_TO_MEM_DIRECTION								0
#define	DMA_u8_MEM_TO_PERIPH_DIRECTION								1
u8 DMA_u8TransferBetweenMemAndPeriph(DMA_Config_t* Copy_DMA_Config_tToConfigure, u32 Copy_u32MemAddress, u32 Copy_u32PeriphAddress, u8 Copy_u8MemSize, u8 Copy_u8PeriphSize, u8 Copy_u8Direction);

u8 DMA_u8SetCallBackFunction(DMA_Config_t* Copy_DMA_Config_tToConfigure, void (*Copy_pf)(void));

u8 DMA_u8EnDisDMA(DMA_Config_t* Copy_DMA_Config_tToConfigure, u8 Copy_u8EnDis);

#endif