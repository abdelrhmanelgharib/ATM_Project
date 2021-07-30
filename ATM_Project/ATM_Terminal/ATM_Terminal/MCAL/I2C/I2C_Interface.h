/*
 * I2C_Interface.h
 *
 *  Created on: Dec 28, 2020
 *      Author: Al Badr
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_





void I2C_MasterInit(void);
void I2C_MasterStart(void);
void I2C_SlaveInit(void);
void I2C_SendSlaveAddressWithWrite(uint8_t address);
void I2C_SendSlaveAddressWithRead(uint8_t address);
void I2C_WriteDataByte(uint8_t data);
uint8_t I2C_ReadDataByte(void);
void I2C_MasterStop(void);
#endif /* I2C_INTERFACE_H_ */
