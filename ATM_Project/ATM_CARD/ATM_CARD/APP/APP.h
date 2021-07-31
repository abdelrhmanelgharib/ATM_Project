/*
 * APP.h
 *
 *  Created on: Jul 25, 2021
 *      Author: Al Badr
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "DataTypes.h"
#include "BIT_MATH.h"
#include "I2C_Interface.h"
#include "EEPROM_interface.h"
#include "UART_int.h"
#include "SER_UART_int.h"
#include "EXTI_int.h"
#include "DIO_Interface.h"
#include "SPI_Interface.h"

#define STRING_EQUL 0
#define INVALID 0
#define VALID 1

/**
 * @brief Initialize all Peripheral
 * 
 */
void APP_Init(void);

/**
 * @brief Store holder name, card number and password on eeprom
 * 
 * @param str 
 */
void Admin_Mode(uint8_t *str);

/**
 * @brief  User Mode
 * 
 * @param str 
 */
void User_Mode(uint8_t *str);

/**
 * @brief Compare two string
 *
 * @param Str1 first string
 * @param Str2 second string
 * @return uint8_t string is equal = 0 or not equal =1
 */
uint8_t String_u8Comp(uint8_t *Str1, uint8_t *Str2);

#endif /* APP_APP_H_ */
