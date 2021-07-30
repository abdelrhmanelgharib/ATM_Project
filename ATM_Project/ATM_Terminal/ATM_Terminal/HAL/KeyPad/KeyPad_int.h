/**
 * @file KeyPad_int.h
 * @author Elgharib
 * @brief KeyPad File Interface
 * @version 0.1
 * @date 2021-07-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

#include "DataTypes.h"
#include "BIT_Math.h"
#include "DIO_Interface.h"
#include "KeyPad_config.h"

/**
 * @brief Initialize KeyPad Pins
 * 
 */
void KEYPAD_voidInit(void);


/**
 * @brief Read Pressed Button on KeyPad and Return Key
 * 
 * @return uint8_t Pressed
 */
uint8_t KEYPAD_u8Read(void);


#endif  /* KEYPAD_INT_H_ */