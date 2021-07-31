/**
 * @file APP.c
 * @author Vicious
 * @brief File Interface
 * @version 0.1
 * @date 2021-07-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "APP.h"

extern uint8_t gFlag;

/**
 * @brief Call Back Function 
 * 
 */
void EX_Callback(void)
{
	if (gFlag == 0)
	{
		SER_UARTvoidSendString("Invalid");
	}
}

/**
 * @brief Initialize all Peripheral
 * 
 */
void APP_Init(void)
{
	UART_ENInit();
	I2C_MasterInit();
	SPI_VidInitSlave();
	DIO_voidSetPinDirection(PORT_D, PIN2, INPUT);
	EXTI_ENEnable(EXTI_INT0);
	EXTI_ENTriggerEdge(EXTI_INT0, FALLING_EDGE);
	EXTI_SetCallBack(EXTI_INT0, EX_Callback);
}

/**
 * @brief Store holder name, card number and password on eeprom
 * 
 * @param str 
 */
void Admin_Mode(uint8_t *str)
{

	SER_UARTvoidSendString((uint8_t *)"Enter Card Holder Name: ");
	SER_UARTvoidReceiveString(str);

	SER_UARTvoidSendString((uint8_t *)"Card Number: ");
	SER_UARTvoidReceiveString(str);
	/* Send Card Number To EEPROM */
	eeprom_send_string(str);

	/* Send Password to EEPROM */
	SER_UARTvoidSendString((uint8_t *)"Enter Passwrod: ");
	SER_UARTvoidReceiveString(str);
	eeprom_send_string(str);

	SPI_U8RecieveByte();
	SPDR = '0';
}

/**
 * @brief  User Mode
 * 
 * @param str 
 */
void User_Mode(uint8_t *str)
{

	SPI_U8RecieveByte();
	SPDR = '1';

	uint8_t i = 0;
	eeprom_recieve_string(str);
	while (SPI_U8RecieveByte() == 'g')
	{
		SPDR = str[i];
		i++;
	}
}

/**
 * @brief Compare two string
 *
 * @param Str1 first string
 * @param Str2 second string
 * @return uint8_t string is equal = 0 or not equal =1
 */
uint8_t String_u8Comp(uint8_t *Str1, uint8_t *Str2)
{
	uint8_t i = 0, Flag = 0;

	while (Str1[i] || Str2[i])
	{
		if (Str1[i] != Str2[i])
		{
			Flag = 1;
			break;
		}
		i++;
	}
	return Flag;
}
