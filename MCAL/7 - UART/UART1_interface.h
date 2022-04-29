#ifndef UART1_INTERFACE_H
#define UART1_INTERFACE_H

#define UART_u16_2400_BAUD_RATE               0xD05 /*((208 << 4) | 5)*/
#define UART_u16_4800_BAUD_RATE               0x683
#define UART_u16_9600_BAUD_RATE               0x341
#define UART_u16_115200_BAUD_RATE             0x45

#define UART1_u8_8DATA_BITS_WORD				0		// not including the start and stop bits but including parity bit
#define UART1_u8_9DATA_BITS_WORD				1

#define UART1_u8_TRANSMIT						0b10
#define UART1_u8_RECEIVE						0b01

typedef struct
{
	u8 wordLength;
	u16 baudRate;
	u8 transmitReceive;
} UART1_config_t;
u8 UART1_u8Init(UART1_config_t* Copy_PUART1_config_tToConfig);

u8 UART1_u8SendWord(u16 Copy_u16Word);

u8 UART1_u8ReceiveWord(u8* Copy_Pu16Word);

#define	UART1_u8_EVEN_PARITY					0
#define	UART1_u8_ODD_PARITY						1
u8 UART1_u8EnableParity(u8 Copy_u8ParitySelection);

#endif
