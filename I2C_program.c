/*
 * MTWI_program.c
 *
 *  Created on: Jun 24, 2019
 *      Author: osama
 */

#include "libraries/L_STD_TYPES.h"
#include "libraries/L_UTILS.h"
#include "I2C_interface.h"
#include "I2C_config.h"
#include "I2C_private.h"



void I2C_voidInit(void) {
	SET_BIT(TWCR, 2); /*enable TWI*/
	/*EEPROM communicates at 100KHz, put 8 @TWBR and 1 @ TWPS and SCL = 100KHz*/
	TWBR = 8;
	CLR_BIT(TWSR, 0);
	CLR_BIT(TWSR, 1);
	/*set my slave address (7-bit) to 0x01 and general call to 0 (LSB)*/
	TWAR = 2;
}

void I2C_voidSendStartCondition(void) {
	/*send start condition*/
	// 1 << 7 clears the flag by writing 1 to it (an internal XOR to the bit,
	// if flag is 1 and I write 1, 1 XOR 1 = 0 (cleared))
	TWCR = (1 << 7) | (1 << 5) | (1 << 2);
	/*block until TWI interrupt flag is raised*/
	while (GET_BIT(TWCR, 7) == 0);
	/*clear start condition bit*/
	TWCR = (1 << 2);
}

void I2C_voidSendStopCondition(void) {
	/*send stop condition*/
	TWCR = (1 << 7) | (1 << 4) | (1 << 2);
	/*block until TWI interrupt flag is raised*/
//	while (GET_BIT(TWCR, 7) == 0);
}

void I2C_voidSendWriteCommand(uint8 Copy_u8SlaveAddress) {
	TWDR = Copy_u8SlaveAddress << 1;
	TWCR = (1 << 7) | (1 << 2);
	while (GET_BIT(TWCR, 7) == 0);
}

void I2C_voidSendReadCommand(uint8 Copy_u8SlaveAddress) {
	TWDR = (Copy_u8SlaveAddress << 1) | 1;
	TWCR = (1 << 7) | (1 << 2);
	while (GET_BIT(TWCR, 7) == 0);
}

void I2C_voidSendByte(uint8 Copy_u8Byte) {
	TWDR = Copy_u8Byte;
	TWCR = (1 << 7) | (1 << 2);
	while (GET_BIT(TWCR, 7) == 0);
}

uint8 I2C_voidReceiveByteWithoutACK(void) {
	TWCR = (1 << 7) | (1 << 2);
	while (GET_BIT(TWCR, 7) == 0);
	return TWDR;
}

uint8 I2C_u8CheckStatus(uint8 Copy_u8ExpectedStatus) {
	uint8 equalFlag;
	if ((TWSR & 0xF8) == Copy_u8ExpectedStatus) {
		equalFlag = 1;
	}else{
		equalFlag = 0;
	}
	return equalFlag;
}

