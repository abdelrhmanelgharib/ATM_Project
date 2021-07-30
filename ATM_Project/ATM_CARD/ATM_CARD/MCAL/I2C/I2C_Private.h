/*
 * I2C_Private.h
 *
 *  Created on: Dec 28, 2020
 *      Author: Al Badr
 */

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWCR    *((volatile u8*)0x56)
#define TWDR    *((volatile u8*)0x23)
#define TWAR    *((volatile u8*)0x22)
#define TWSR    *((volatile u8*)0x21)
#define TWBR    *((volatile u8*)0x20)

#endif /* I2C_PRIVATE_H_ */
