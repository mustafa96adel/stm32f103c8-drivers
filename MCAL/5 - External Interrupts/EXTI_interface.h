/************************************************************/
/***************** Name    : Mustafa Adel  ******************/
/***************** Date    : 26/7/2021     ******************/
/***************** Version : 1.0           ******************/
/***************** SWC     : RCC           ******************/
/************************************************************/

#ifndef  EXTI_INTERFACE_H
#define  EXTI_INTERFACE_H

#define EXTI_LINE0                  (0)
#define EXTI_LINE1                  (1)
#define EXTI_LINE2                  (2)
#define EXTI_LINE3                  (3)
#define EXTI_LINE4                  (4)
#define EXTI_LINE5_9                (5)
#define EXTI_LINE10_15              (6)

u8 EXTI_u8SetInterruptStatus (u8 Copy_u8LineNumber, u8 Copy_u8Status);

#define	EXTI_u8_FALLING_EDGE				1
#define EXTI_u8_RISING_EDGE					0
u8 EXTI_u8SetInterruptEdge   (u8 Copy_u8LineNumber, u8 Copy_u8Edge);

u8 EXTI_u8ClearInterruptPending(u8 Copy_u8LineNumber);

u8 EXTI_u8IsInterruptActive(u8 Copy_u8LineNumber, u8* Copy_u8Status);

#endif
