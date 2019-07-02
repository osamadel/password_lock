#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "MUART_private.h"
#include "MUART_interface.h"
#include "MUART_config.h"

void MUART_voidInit (void) {

	uint8 ucsrc = 0b10000000;
	/* initialize double speed bit */
	#if MUART_DOUBLE_SPEED == 1
		SET_BIT(UCSRA, 1);
	#else
		CLR_BIT(UCSRA, 1);
	#endif



	 /*initialize multiprocessor communication bit*/
	#if MUART_MULTI_PROCESSOR == 1
		SET_BIT(UCSRA, 0);
	#else
		CLR_BIT(UCSRA, 0);
	#endif


	/* initialize RX complete interrupt enable bit */
	#if MUART_RX_INT_EN == 1
		SET_BIT(UCSRB, 7);
	#else
		CLR_BIT(UCSRB, 7);
	#endif




	 /*initialize TX complete interrupt enable bit*/
	#if MUART_TX_INT_EN == 1
		SET_BIT(UCSRB, 6);
	#else
		CLR_BIT(UCSRB, 6);
	#endif




	 /*initialize data registry empty interrupt enable bit*/
	#if MUART_UDR_EMPTY_INT_EN == 1
		SET_BIT(UCSRB, 5);
	#else
		CLR_BIT(UCSRB, 5);
	#endif


	SET_BIT(UCSRB, 4);      // Enable RXB
	SET_BIT(UCSRB, 3);      // Enable TXB

	CLR_BIT(UCSRB, 2);

	/*accessing UCSRC*/
	#if MUART_CHARACTER_SIZE == MUART_5_BIT
		CLR_BIT(UCSRB, 2);
		CLR_BIT(ucsrc, 2);
		CLR_BIT(ucsrc, 1);
	#elif MUART_CHARACTER_SIZE == MUART_6_BIT
		CLR_BIT(UCSRB, 2);
		CLR_BIT(ucsrc, 2);
		SET_BIT(ucsrc, 1);
	#elif MUART_CHARACTER_SIZE == MUART_7_BIT
		CLR_BIT(UCSRB, 2);
		SET_BIT(ucsrc, 2);
		CLR_BIT(ucsrc, 1);
	#elif MUART_CHARACTER_SIZE == MUART_8_BIT
		CLR_BIT(UCSRB, 2);
		SET_BIT(ucsrc, 2);
		SET_BIT(ucsrc, 1);
	#elif MUART_CHARACTER_SIZE == MUART_9_BIT
		SET_BIT(UCSRB, 2);
		SET_BIT(ucsrc, 2);
		SET_BIT(ucsrc, 1);
	#else
		report error
		#error "Unidentified character size configuration"
	#endif





	 /*initialize synch/asynch bit*/
	#if MUART_MODE == MUART_ASYNCH
		CLR_BIT(ucsrc, 6);
	#else
		SET_BIT(ucsrc, 6);
	#endif



	#if MUART_CLK_POLARITY == MUART_POL_CHANGE_SAMPLE
		CLR_BIT(ucsrc, 0);
	#else
		SET_BIT(ucsrc, 0);
	#endif


	/* initialize parity*/
	#if MUART_PARITY == MUART_NO_PARITY
			CLR_BIT(ucsrc, 5);
			CLR_BIT(ucsrc, 4);
	#elif MUART_PARITY == MUART_PARITY_EVEN
			SET_BIT(ucsrc, 5);
			CLR_BIT(ucsrc, 4);
	#elif MUART_PARITY == MUART_PARITY_ODD
			SET_BIT(ucsrc, 5);
			SET_BIT(ucsrc, 4);
	#else
		report error
		#error "Unidentified parity configuration"
	#endif





	 /*initialize stop bit*/
	#if MUART_STOP_BIT == MUART_STOP_2BIT
		SET_BIT(ucsrc, 3);
	#elif MUART_STOP_BIT == MUART_STOP_1BIT
		CLR_BIT(ucsrc, 3);
	#else
		#error "Unidentified stop bit configuration"
	#endif



	UCSRC = ucsrc;

	/* initialize baud rate */
	UBRRH = 0;
	UBRRL = MUART_BAUDRATE;

}


void MUART_voidSendByte (uint8 Copy_u8Byte) {
    while(GET_BIT(UCSRA, 5) == 0);
    UDR = Copy_u8Byte;
}


uint8 MUART_u8ReceiveByte (void) {
    while (GET_BIT(UCSRA, 7) == 0);
    return UDR;
}
