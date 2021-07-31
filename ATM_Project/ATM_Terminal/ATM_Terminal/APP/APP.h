/**
 * @file APP.h
 * @author Vicious
 * @brief File Interface
 * @version 0.1
 * @date 2021-07-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ATM_TERMINAL_APP_H_
#define ATM_TERMINAL_APP_H_

#include "DataTypes.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "UART_int.h"
#include "SER_UART_int.h"
#include "I2C_Interface.h"
#include "EEPROM_interface.h"
#include "LCD16x2.h"
#include "KeyPad_int.h"
#include "EXTI_int.h"
#include "SPI_Interface.h"
#include "MOTOR_Interface.h"
#include "ADC_Interface.h"
#include "LM_35_Interface.h"
#include <util/delay.h>



#define STRING_EQUL 0
#define INVALID 0
#define VALID 1
#define INCORRECT 0
#define CORRECT 1

#define TEMP_MODE    '1'
#define ATM_MODE     '2'

/**
 * @brief Call Back Function 
 * 
 */
void EX_Callback(void);

/**
 * @brief Initialize all Peripheral
 * 
 */
void APP_Init(void);

/**
 * @brief Home Screen for ATM ask for ATM OR Temperature
 * 
 * @return uint8_t keypad Pressed Value
 */
uint8_t ADC_ATM(void);

/**
 * @brief This function for Admin Mode to store data on eeprom and enter new number, balance and MaxAmount 
 * 
 */
void ADMIN_Mode(void);

/**
 * @brief This Function For user Mode to check user password and deposit and turn on motor if Approved
 * 
 */
void USER_Mode(void);

/**
 * @brief compare user enter money and balance
 * 
 * @param Max_money MAX AMOUNT Cal withdraw
 * @param User_money Deposit 
 * @return uint8_t* VALID | INVALID
 */
uint8_t Compare_Money(uint32_t Max_money, uint32_t User_money);

/**
 * @brief Check for Passwrod 
 * 
 * @param Card_Pass store passwrod on Card_Pass
 * @return uint8_t CORRECT | INCORRECT
 */
uint8_t Pass_check(uint8_t *card);

/**
 * @brief Display Temp on Lcd if user select Temp Mode
 * 
 */
void TEMP(void);

/**
 * @brief Compare two string
 * 
 * @param Str1 first string
 * @param Str2 second string
 * @return uint8_t string is equal = 0 or not equal =1 
 */
uint8_t String_u8Comp(uint8_t *Str1, uint8_t *Str2);

/**
 * @brief send garbag value to slave to receive his own data
 * 
 * @param str receive data form slave
 */
void Get_Pass(uint8_t *str);

/**
 * @brief Convert String to Number 
 * 
 * @param Str Pointer to the first element in the array
 * @return uint32_t Number after Converted to Real Numb
 */
uint32_t String_u8ToNumb(uint8_t *Str);

#endif /* ATM_TERMINAL_APP_H_ */
