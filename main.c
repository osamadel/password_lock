#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "HLCD_interface.h"
#include "HEEPROM_interface.h"
#include "MUART_interface.h"
#include "HKeyPad_interface.h"
#include <util/delay.h>

//#define SET_PASS

void UART_sendText(uint8 * text);
void UART_receiveText(uint8 * text);
void getKeyPadPassword(uint8 * password);
uint8 checkPassword(uint8 * password, uint8 * reference);

int main(void) {
	uint8 rMessage[255];
	uint8 password[255];
	uint8 EEPROM_index = 0;
	sint8 tryCount = 3;
	uint16 i;

	MUART_voidInit();
	EEPROM_voidInit();
	HLCD_init(HLCD_8_BIT);
	HKeyPad_init();

#ifdef SET_PASS
	HLCD_writeText("Waiting password");
	UART_sendText("Please enter password:");
	UART_receiveText(rMessage);

	HLCD_clear();
	HLCD_writeText("Password:");
	HLCD_setCursor(1, 0);
	HLCD_writeText(rMessage);
	for (i=0; rMessage[i] != '\0'; i++) {
		EEPROM_voidWriteByte(rMessage[i], i);
		_delay_ms(2);
	}
	EEPROM_voidWriteByte(rMessage[i], i); // write '\0'
	_delay_ms(2);
	EEPROM_voidWriteByte(3, 256); // write 3
	_delay_ms(1000);
	HLCD_clear();
	HLCD_writeText("Password Set");
//	_delay_ms(1000);
#else

	EEPROM_voidReadByte(&tryCount, 256);
	HLCD_clear();
	HLCD_writeInt(tryCount);
	_delay_ms(1000);
	if (tryCount == 0) {
		HLCD_clear();
		HLCD_writeText("SYSTEM LOCKED");
	} else {

		for (;;) {
			EEPROM_index = 0;
			HLCD_clear();
			HLCD_writeText("Enter Password:");
			HLCD_setCursor(1, 0);
			getKeyPadPassword(password);
	//		HLCD_clear();
	//		HLCD_writeText("After keypad");



			do {
				EEPROM_voidReadByte(&rMessage[EEPROM_index], EEPROM_index);
			} while (rMessage[EEPROM_index++] != '\0');



			HLCD_clear();
			HLCD_writeText("comparing...");
			HLCD_writeText(password);
			_delay_ms(1000);

			if (checkPassword(password, rMessage)) {
				HLCD_clear();
				HLCD_writeText("CORRECT");
				EEPROM_voidWriteByte(3, 256); // write 3
//				_delay_ms(1000);
				break;
			} else if (tryCount > 0){
				HLCD_clear();
				HLCD_writeText("WRONG");
				HLCD_setCursor(1, 0);
				HLCD_writeInt((tryCount--));
				HLCD_writeText(" trys left");
				EEPROM_voidWriteByte(tryCount, 256);
				_delay_ms(1000);
			} else if (tryCount <= 0) {
				HLCD_clear();
				HLCD_writeText("SYSTEM LOCKED");
				break;
			}

		}
	}
#endif
	return 0;
}



void UART_sendText(uint8 * text) {
	for (uint8 i = 0; text[i] != '\0'; i++) {
		MUART_voidSendByte(text[i]);
	}
	MUART_voidSendByte('\n');
}



void UART_receiveText(uint8 * text) {
	uint8 rByte;
	while ((rByte = MUART_u8ReceiveByte()) != '\n') {
		*text = rByte;
		text++;
	}
	*text = '\0';
}



void getKeyPadPassword(uint8 * password) {
	uint8 keyNumber;
	while ((keyNumber = HKeyPad_getKey()) != '=') {
//		HLCD_writeData(keyNumber);
		if (keyNumber != 0 && keyNumber >= '0' && keyNumber <= '9') {
//			HLCD_writeData('2');
			HLCD_writeData(keyNumber);
			*password = keyNumber;
			password++;
		}
		*password = '\0';
		_delay_ms(200);
	}
}



uint8 checkPassword(uint8 * password, uint8 * reference) {
	uint8 equality_flag = 1;
	while (*password != '\0' || *reference != '\0') {
		if (*password != *reference) {
			equality_flag = 0;
			break;
		}
		password++;
		reference++;
	}
	return equality_flag;
}
