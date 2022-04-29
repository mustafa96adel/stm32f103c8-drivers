/***********************************************************************/
/*************** Name 	 : Mustafa Adel	 *******************************/
/*************** Date 	 : 5 / 7 / 2021	 *******************************/
/*************** Version : 1.0           *******************************/
/*************** SWC     : RCC			 *******************************/
/***********************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H
#include "STD_TYPES.h"

void RCC_u8EnableHSE();
void RCC_u8EnableHSI();

#define RCC_u8_PLL_SOURCE_HSI_DIVIDED_BY_2					0
#define RCC_u8_PLL_SOURCE_HSE								1
u8 RCC_u8enablePll(u8 Copy_u8MulFactor /* Any number from 2 to 16 */,u8 Copy_u8PLLSource);

#define RCC_u8_NO CLOCK										0b0000 
#define RCC_u8_SYSTEM_CLOCK									0b0100 
#define RCC_u8_HSI_CLOCK									0b0101 
#define RCC_u8_HSE_CLOCK									0b0110 
#define RCC_u8_PLL_CLOCK_DIVIDED_BY_2						0b0111 
u8 RCC_u8SetMCO(u8 Copy_u8Source);

enum{
	RCC_EnmU8DMA1,
	RCC_EnmU8DMA2,
	RCC_EnmU8SPAM,
	RCC_EnmU8FLITF = 4,
	RCC_EnmU8CRCE = 6,
	RCC_EnmU8FSMC = 8,
	RCC_EnmU8SDIO = 10,
	RCC_EnmU8AFIO = 32,
	RCC_EnmU8IOPA = 34,
	RCC_EnmU8IOPB, 
	RCC_EnmU8IOPC, 
	RCC_EnmU8IOPD, 
	RCC_EnmU8IOPE,
	RCC_EnmU8IOPF,
	RCC_EnmU8IOPG,
	RCC_EnmU8ADC1,
	RCC_EnmU8ADC2,
	RCC_EnmU8TIM1,
	RCC_EnmU8SPI1,
	RCC_EnmU8TIM8,
	RCC_EnmU8USART,
	RCC_EnmU8ADC3,
	RCC_EnmU8TIM9 = 51,
	RCC_EnmU8TIM10,
	RCC_EnmU8TIM11, 
	RCC_EnmU8TIM2 = 64,
	RCC_EnmU8TIM3,
	RCC_EnmU8TIM4,
	RCC_EnmU8TIM5,
	RCC_EnmU8TIM6,
	RCC_EnmU8TIM7,
	RCC_EnmU8TIM12,
	RCC_EnmU8TIM13,
	RCC_EnmU8TIM14,
	RCC_EnmU8WWDG = 75,
	RCC_EnmU8SPI2 = 78,
	RCC_EnmU8SPI3,
	RCC_EnmU8USART2 = 81,
	RCC_EnmU8USART3,
	RCC_EnmU8USART4,
	RCC_EnmU8USART5,
	RCC_EnmU8I2C1,
	RCC_EnmU8I2C2,
	RCC_EnmU8USB,
	RCC_EnmU8CAN = 89,
	RCC_EnmU8BKP = 91,
	RCC_EnmU8PWR,
	RCC_EnmU8DAC};
u8 RCC_u8EnablePeripheralClk(u8 Copy_u8PeripheralID);
u8 RCC_u8DisablePeripheralClk(u8 Copy_u8PeripheralID);

#endif
