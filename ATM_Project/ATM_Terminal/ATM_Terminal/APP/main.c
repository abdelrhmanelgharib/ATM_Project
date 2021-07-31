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

#include "APP.h"

uint8_t volatile card_gflag = 0;
uint8_t volatile gflag = 0;
extern volatile uint8_t CallBackFLag;

int main()
{
	uint8_t Data[55];
	uint8_t value = 0;
	uint8_t *Admin = (uint8_t *)"ADMIN";
	uint8_t *User = (uint8_t *)"USER";

	APP_Init();

	while (1)
	{
		value = ADC_ATM();
		if (value == TEMP_MODE)
		{
			TEMP();
		}
		else if (value == ATM_MODE)
		{
			SER_UARTvoidSendString((uint8_t *)"you want ADMIN or USER MODE: ");
			SER_UARTvoidReceiveString(Data);

			/* Admin */
			if (String_u8Comp(Data, Admin) == STRING_EQUL)
			{
				gflag = INVALID;

				ADMIN_Mode();
			}
			else if (String_u8Comp(Data, User) == STRING_EQUL)
			{
				static uint8_t FlFag = 5;
				gflag = VALID;
				if (5 == FlFag)
				{
					SPI_VidSendByte('g');
					uint8_t b1 = SPI_U8RecieveByte();
					SPI_VidSendByte('g');
					card_gflag = SPI_U8RecieveByte();
					FlFag = VALID;
				}

				SER_UARTvoidSendString((uint8_t *)"waiting for card to insert");
				while (CallBackFLag != VALID)
					;
				USER_Mode();
				CallBackFLag = INVALID;
			}
		}
		else
		{
			lcd_clear();
			lcd_sendString((uint8_t *)"Wrong Enter");
			_delay_ms(1000);
		}
	}
}
