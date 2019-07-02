/*
 * MTWI_interface.h
 *
 *  Created on: Jun 24, 2019
 *      Author: osama
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

void I2C_voidInit(void);

void I2C_voidSendStartCondition(void);

void I2C_voidSendStopCondition(void);

void I2C_voidSendWriteCommand(uint8 Copy_u8SlaveAddress);

void I2C_voidSendReadCommand(uint8 Copy_u8SlaveAddress);

void I2C_voidSendByte(uint8 Copy_u8Byte);

uint8 I2C_voidReceiveByteWithoutACK(void);

uint8 I2C_u8CheckStatus(uint8 Copy_u8ExpectedStatus);

#define START_C_SENT					0x08
#define R_START_C_SENT					0x10
#define SLA_W_ACK 						0x18
#define SLA_W_NO_ACK					0x20
#define BYTE_SENT_ACK					0x28
#define BYTE_SENT_NO_ACK				0x30
#define ARBIT_LOST						0x38
#define SLA_R_ACK						0x40
#define SLA_R_NO_ACK					0x48
#define BYTE_READ_ACK					0x50
#define BYTE_READ_NO_ACK				0x58

#endif /* I2C_INTERFACE_H_ */
