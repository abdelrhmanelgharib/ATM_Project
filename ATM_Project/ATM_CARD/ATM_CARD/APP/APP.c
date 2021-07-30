/*
 * APP.c
 *
 *  Created on: Jul 25, 2021
 *      Author: Al Badr
 */

#include "DataTypes.h"
#include "BIT_MATH.h"
#include "I2C_Interface.h"
#include "EEPROM_interface.h"
#include "UART_int.h"
#include "SER_UART_int.h"
#include "EXTI_int.h"
#include "DIO_Interface.h"
#include "SPI_Interface.h"

extern uint8_t gFlag;

void EX_Callback(void)
{
	if(gFlag == 0)
	{
		SER_UARTvoidSendString("Invalid");
	}
}

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

void Admin_Mode(uint8_t *str){

	SER_UARTvoidSendString("Enter Card Holder Name");
	SER_UARTvoidReceiveString(str);

	SER_UARTvoidSendString("Card Number");
	SER_UARTvoidReceiveString(str);
	/* Send Card Number To EEPROM */
	eeprom_send_string(str);

	/* Send Password to EEPROM */
	SER_UARTvoidSendString("Enter Passwrod");
	SER_UARTvoidReceiveString(str);
	eeprom_send_string(str);

	SPI_U8RecieveByte();
	SPDR='0';

}
void User_Mode(uint8_t *str){

	SPI_U8RecieveByte();
	SPDR='1';

	uint8_t value, i=0;
	eeprom_recieve_string(str);
	//SER_UARTvoidSendString(str);
	//SPDR = str[0];
	while(SPI_U8RecieveByte() == 'g')
	{

		//SPDR = str[0];
		SPDR = str[i];
		//SPI_VidSendByte(str[i]);

		i++;
		//uint8_t x = SPI_U8RecieveByte();
	}


	//SER_UARTvoidSendString(str);
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
