/************************************************************/
/***************** Name    : Mustafa Adel  ******************/
/***************** Date    : 8/8/2021      ******************/
/***************** Version : 3.0           ******************/
/***************** SWC     : SYSTICK       ******************/
/************************************************************/
#ifndef SSTK_INTERFACE_H
#define SSTK_INTERFACE_H

#define SSTK_u8_AHB_NO_DIV					1
#define SSTK_u8_AHB_DIV_BY_8				0
u8 SSTK_u8AHBMode(u8 Copy_u8AHBDiv);

//		edit them to be functions

void 	SSTK_voidRun				(void);

void 	SSTK_voidStop				(void);

void	SSTK_voidPause				(void);

void	SSTK_voidEnableInterrupts	(void);

void 	SSTK_voidDisableInterrupts  (void);

u32 	SSTK_u32ElapsedTime			(void);

u32 	SSTK_u32RemainingTime		(void);

void	SSTK_voidSetCallBackFunction(void (*Copy_pf)(void));

u8		SSTK_u8SetRELOADReg(u32 Copy_u32LoadValue);

u8 SSTK_u8SetBusyWait(u32 Copy_u32NumOfTicks);

u8 SSTK_u8SetIntervalSingle(u32 Copy_u32NumOfTicks);

u8 SSTK_u8SetIntervalPeriodic(u32 Copy_u32NumOfTicks);


#endif
