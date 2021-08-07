/**
 * @file main.c
 * @author Vicious
 * @brief main.c
 * @version 0.1
 * @date 2021-07-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "DataTypes.h"
#include "BIT_MATH.h"
#include "APP.h"
#include "UART_int.h"
#include "SPI_Interface.h"
#include "SER_UART_int.h"
#include "SPI_Interface.h"
#include "DIO_Interface.h"
#include "avr/delay.h"
uint8_t gFlag = 0;

volatile uint8_t data_arr[100];

int main()
{
	uint8_t Data[55];
	uint8_t Data1[55];
	uint8_t *Admin = (uint8_t *)"ADMIN";
	uint8_t *User = (uint8_t *)"USER";

	APP_Init();
	UART_voidReceiveString_Ashync(data_arr);
	while (1)
	{
		UART_voidRXInterruptDisable();
		SER_UARTvoidSendString("you want user or admin mode ?");

		SER_UARTvoidReceiveString(Data1);
		SER_UARTvoidReceiveString(Data1);
		SER_UARTvoidSendString(Data1);

		/* Admin */
		if (String_u8Comp(Data1, Admin) == STRING_EQUL)
		{
			gFlag = INVALID;

			Admin_Mode(Data);
		}
		else if (String_u8Comp(Data1, User) == STRING_EQUL)
		{
			gFlag = VALID;

			User_Mode(Data);
		}
		else
		{
			SER_UARTvoidSendString((uint8_t *)"Wrong Enter");
		}
	}
}
