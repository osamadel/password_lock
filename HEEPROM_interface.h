/*
 * EEPROM_interface.h
 *
 *  Created on: Jun 27, 2019
 *      Author: osama
 */

#ifndef HEEPROM_INTERFACE_H_
#define HEEPROM_INTERFACE_H_

void EEPROM_voidInit();

void EEPROM_voidWriteByte(uint8 byte, uint16 location);

void EEPROM_voidReadByte(uint8 * byte, uint16 location);



#endif /* HEEPROM_INTERFACE_H_ */
