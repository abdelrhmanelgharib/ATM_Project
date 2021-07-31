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

uint8_t gFlag = 0;

int main()
{
	uint8_t Data[55];
	uint8_t *Admin = (uint8_t *)"ADMIN";
	uint8_t *User = (uint8_t *)"USER";
	APP_Init();

	while (1)
	{
		SER_UARTvoidReceiveString(Data);
		/* Admin */
		if (String_u8Comp(Data, Admin) == STRING_EQUL)
		{
			gFlag = INVALID;

			Admin_Mode(Data);
		}
		else if (String_u8Comp(Data, User) == STRING_EQUL)
		{
			gFlag = VALID;

			User_Mode(Data);

			if (String_u8Comp(Data, Admin) == STRING_EQUL)
			{
				Admin_Mode(Data);
			}
		}
		else
		{
			SER_UARTvoidSendString((uint8_t *)"Wrong Enter");
		}
	}
}
