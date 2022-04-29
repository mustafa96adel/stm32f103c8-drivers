/***********************************************************************/
/*************** Name 	 : Mustafa Adel	 *******************************/
/*************** Date 	 : 6 / 7 / 2021	 *******************************/
/*************** Version : 1.0           *******************************/
/*************** SWC     : GPIO			 *******************************/
/***********************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/* Macros for "port" */
#define GPIO_u8_PORT_A						                    0
#define GPIO_u8_PORT_B						                    1
#define GPIO_u8_PORT_C						                    2
#define GPIO_u8_PORT_D						                    3
#define GPIO_u8_PORT_E						                    4
#define GPIO_u8_PORT_F						                    5


/* Macros for "pinMode" */
#define GPIO_u8_GPO_PUSH_PULL_2MHZ								0b0010
#define GPIO_u8_GPO_PUSH_PULL_10MHZ								0b0001
#define GPIO_u8_GPO_PUSH_PULL_50MHZ								0b0011
		
#define GPIO_u8_GPO_OPEN_DRAIN_2MHZ								0b0110
#define GPIO_u8_GPO_OPEN_DRAIN_10MHZ							0b0101
#define GPIO_u8_GPO_OPEN_DRAIN_50MHZ							0b0111
		
#define GPIO_u8_AFIO_PUSH_PULL_2MHZ								0b1010
#define GPIO_u8_AFIO_PUSH_PULL_10MHZ                            0b1001
#define GPIO_u8_AFIO_PUSH_PULL_50MHZ                            0b1011
		
#define GPIO_u8_AFIO_OPEN_DRAIN_2MHZ							0b1110
#define GPIO_u8_AFIO_OPEN_DRAIN_10MHZ                           0b1101
#define GPIO_u8_AFIO_OPEN_DRAIN_50MHZ                           0b1111
		
#define GPIO_u8_INPUT_PULLUP									0b10001
#define GPIO_u8_INPUT_PULLDOWN									0b10000
#define GPIO_u8_INPUT_ANALOG									0b0000
#define GPIO_u8_INPUT_FLOAT										0b0100
typedef struct
{
	u8 port;
	u8 pinNumber;							/* Ranges from 0 to 15 */
	u8 pinMode;
} GPIO_Pin;

u8 GPIO_u8PinInit(GPIO_Pin* Copy_StrPin);

#define GPIO_u8_LOW												0
#define GPIO_u8_HIGH											1
u8 GPIO_u8SetPinOutput(GPIO_Pin* Copy_StrPin, u8 Copy_u8PinValue);

u8 GPIO_u8GetPinInput(GPIO_Pin* Copy_StrPin);

u8 GPIO_u8SetPortOutput(u8 Copy_u8Port, u8 Copy_u8PortValue);

u16 GPIO_u8GetPortInput(u8 Copy_u8Port);

u8 GPIO_u8TogglePin(GPIO_Pin* Copy_StrPin);

#endif
