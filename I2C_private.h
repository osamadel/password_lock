/*
 * MTWI_private.h
 *
 *  Created on: Jun 24, 2019
 *      Author: osama
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWCR *((volatile uint8 *)(0x56))
#define TWDR *((volatile uint8 *)(0x23))
#define TWAR *((volatile uint8 *)(0x22))
#define TWSR *((volatile uint8 *)(0x21))
#define TWBR *((volatile uint8 *)(0x20))


#endif /* I2C_PRIVATE_H_ */
