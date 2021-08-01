/**
 * @file LCD_Interface.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


#include "DataTypes.h"
#include "BIT_Math.h"
#include "DIO_Interface.h"
#include "LCD_config.h"


#include <avr/delay.h>


/**
 * @brief Initialize LCD Pins and LCD Mode
 * 
 * Select Mode From Config.h File LCD_enum_8BITS_MODE - LCD_enum_4BITS_MODE
 */
void LCD_voidInit(void);


/**
 * @brief Send Command to Lcd
 * 
 * @param command Command
 */
void LCD_voidSendCommand(uint8_t command);


/**
 * @brief Write One Byte On Lcd
 * 
 * @param ch Byte to write
 */
void LCD_voidWriteChar(uint8_t);


/**
 * @brief Write String On Lcd
 * 
 * @param str Pointer to The First Element of the String
 */
void LCD_voidWriteString(uint8_t* str);


/**
 * @brief Write Unsigned Integer On Lcd
 * 
 * @param number Unsinged Number
 */
void LCD_voidPrintUnsignedInteger(uint32_t number);


/**
 * @brief Write signed Integer On Lcd
 * 
 * @param number Signed Number
 */
void LCD_voidPrintSignedInteger(sint32_t number);

/**
 * @brief This Function to Control Write On LCD Position
 * 
 * @param raw raw
 * @param col column
 */
void LCD_voidGoto(uint8_t raw , uint8_t col);

/**
 * @brief Clear Lcd
 * 
 */
void LCD_voidCLRDisplay(void);






#endif  /* LCD_INTERFACE_H_ */
