/*
 * EEPROM_program.c
 *
 *  Created on: Jun 27, 2019
 *      Author: osama
 */

#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "I2C_interface.h"
#include "HEEPROM_interface.h"
#include "HLCD_interface.h"
#include "util/delay.h"

#define DELAY 1000
#define DEBUG 0
#define DEBUG2 0

/* **********************************************************
 * initialize I2C communication with EEPROM
 * **********************************************************/
void EEPROM_voidInit() {
	I2C_voidInit();
#if DEBUG == 1
	HLCD_clear();
	HLCD_writeText("init");
	_delay_ms(DELAY);
#endif
}
/************************************************************/


/* **********************************************************
 * Write one byte to EEPROM at address "location" from 1024
 * possible addresses. "location" is 16-bit variable but
 * the loaded address should only be 10-bit value.
 * **********************************************************/
void EEPROM_voidWriteByte(uint8 byte, uint16 location) {
	uint8 SLA_W_R = 0;
	location = 0x03FF & location;
	uint8 pageNumber = (location) >> 8;
#if DEBUG == 1
	HLCD_clear();
	HLCD_writeText("WriteByte ..");
	_delay_ms(DELAY);
#endif

	I2C_voidSendStartCondition();
	SLA_W_R = (0xA0 >> 1) | pageNumber;
	I2C_voidSendWriteCommand(SLA_W_R);
	if (I2C_u8CheckStatus(SLA_W_ACK) != 1) {
#if DEBUG == 1
		HLCD_clear();
		HLCD_writeText("SLA+W not sent");
		_delay_ms(DELAY);
#endif
		return;
	}

#if DEBUG == 1
	HLCD_clear();
	HLCD_writeText("SLA+W sent");
	_delay_ms(DELAY);
#endif


	I2C_voidSendByte((uint8)location);
	if (I2C_u8CheckStatus(0x28) != 1) {
#if DEBUG == 1
		HLCD_clear();
		HLCD_writeText("location not sent");
		_delay_ms(DELAY);
#endif
		return;
	}
#if DEBUG == 1
	HLCD_clear();
	HLCD_writeText("location sent");
	_delay_ms(DELAY);
#endif

	I2C_voidSendByte(byte);
	if (I2C_u8CheckStatus(0x28) != 1) {
#if DEBUG == 1
		HLCD_clear();
		HLCD_writeText("byte not sent");
		_delay_ms(DELAY);
#endif
		return;
	}
#if DEBUG == 1
	HLCD_clear();
	HLCD_writeText("byte sent");
	_delay_ms(DELAY);
#endif

	I2C_voidSendStopCondition();
}
/************************************************************/




/* **********************************************************
 * Reads one byte from EEPROM at address "location" from 1024
 * possible addresses to pointer of type uint8 "byte".
 * "location" is 16-bit variable but the loaded address
 * should only be 10-bit value.
 * **********************************************************/
void EEPROM_voidReadByte(uint8 * byte, uint16 location) {
	uint8 SLA_W_R = 0;
	location = 0x03FF & location;
	uint8 pageNumber = (location) >> 8;
	/*send starting condition bit*/
	I2C_voidSendStartCondition();
	if (I2C_u8CheckStatus(START_C_SENT) != 1) {
		return;
	}
	/*send the slave address (includes page number) + write
	 * command*/
	SLA_W_R = (0xA0 >> 1) | pageNumber;
	I2C_voidSendWriteCommand(SLA_W_R);
	if (I2C_u8CheckStatus(SLA_W_ACK) != 1) {
#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("SLA+W not sent");
		_delay_ms(DELAY);
#endif
		return;
	}

#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("SLA+W sent");
		_delay_ms(DELAY);
#endif


	/*send the location byte inside the page*/
	I2C_voidSendByte((uint8)location);
	if (I2C_u8CheckStatus(BYTE_SENT_ACK) != 1) {
#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("location not sent");
		_delay_ms(DELAY);
#endif
		return;
	}

#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("location sent");
		_delay_ms(DELAY);
#endif

	/*send a restart condition bit*/
	I2C_voidSendStartCondition();
	if (I2C_u8CheckStatus(R_START_C_SENT) != 1) {
#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("restart condition not sent");
		_delay_ms(DELAY);
#endif
		return;
	}

#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("restart condition sent");
		_delay_ms(DELAY);
#endif


	/*send a slave address (includes the page number) + read
	 * command*/
	SLA_W_R = (0xA0 >> 1) | pageNumber;
	I2C_voidSendReadCommand(SLA_W_R);
	if (I2C_u8CheckStatus(SLA_R_ACK) != 1) {
#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("SLA+R not sent");
		_delay_ms(DELAY);
#endif
		return;
	}


#if DEBUG2 == 1
		HLCD_clear();
		HLCD_writeText("SLA+R sent");
		_delay_ms(DELAY);
#endif

	/*read the received byte*/
	*byte = I2C_voidReceiveByteWithoutACK();
//	if (I2C_u8CheckStatus(BYTE_READ_ACK) != 1) {
//		HLCD_clear();
//		HLCD_writeText("byte not received");
//		_delay_ms(DELAY);
//		return;
//	}
	/*send a stop condition*/
	I2C_voidSendStopCondition();
}
/************************************************************/
