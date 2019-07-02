#ifndef _MUART_INTERFACE_H_
#define _MUART_INTERFACE_H_

/* ********************************* */

/* 
* Function Description: The function is to initialize UART peripheral
* 
* Input Parameters: void
* Output Parameters: void
*/
void MUART_voidInit (void);

/* 
* Function Description: The function is to send one byte
* 
* Input Parameters: uint8
* Output Parameters: void
*/
void MUART_voidSendByte (uint8 Copy_u8Byte);

/* 
* Function Description: The function is to receive one byte
* 
* Input Parameters: void
* Output Parameters: uint8
*/
uint8 MUART_u8ReceiveByte (void);


#define MUART_U8_BAUDRATE_2400			207
#define MUART_U8_BAUDRATE_4800			103
#define MUART_U8_BAUDRATE_9600			51
#define MUART_U8_BAUDRATE_14400			34
#define MUART_U8_BAUDRATE_19200			25
#define MUART_U8_BAUDRATE_28800			16
#define MUART_U8_BAUDRATE_38400			12
#define MUART_U8_BAUDRATE_57600			8
#define MUART_U8_BAUDRATE_76800			6
#define MUART_U8_BAUDRATE_115200		3
#define MUART_U8_BAUDRATE_230400		1
#define MUART_U8_BAUDRATE_500000		0

#define MUART_5_BIT					0
#define MUART_6_BIT					1
#define MUART_7_BIT					2
#define MUART_8_BIT					3
#define MUART_9_BIT					9

#define MUART_ASYNCH				0
#define MUART_SYNCH					1

#define MUART_NO_PARITY				0
#define MUART_PARITY_EVEN			2
#define MUART_PARITY_ODD			3

#define MUART_STOP_1BIT				0
#define MUART_STOP_2BIT				1

#define MUART_POL_CHANGE_SAMPLE		0
#define MUART_POL_SAMPLE_CHANGE		1



#endif
