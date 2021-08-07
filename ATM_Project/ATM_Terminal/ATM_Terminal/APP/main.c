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
extern volatile uint8_t BUTTONFLag;

int main()
{
	uint8_t Data1[55]= {0};
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
			SER_UARTvoidReceiveString(Data1);
			SER_UARTvoidReceiveString(Data1);

			/* Admin */
			if (String_u8Comp(Data1, Admin) == STRING_EQUL)
			{
				SPI_VidSendByte('f');
				uint8_t B1 = SPI_U8RecieveByte();
				gflag = INVALID;

				ADMIN_Mode();
			}
			else if (String_u8Comp(Data1, User) == STRING_EQUL)
			{
				SPI_VidSendByte('f');
				uint8_t B1 = SPI_U8RecieveByte();
				gflag = VALID;

				SER_UARTvoidSendString((uint8_t *)"waiting for card to insert");
				while (BUTTONFLag != VALID)
					;

				if (CallBackFLag == VALID)
				{
					SER_UARTvoidSendString("USERMODE");
					USER_Mode();
				}
				BUTTONFLag = INVALID;
			}
			else
			{
				SER_UARTvoidSendString((uint8_t *)"Wrong Enter");
			}
		}
		else
		{
			LCD_voidCLRDisplay();
			LCD_voidWriteString((uint8_t *)"Wrong Enter ");
			LCD_voidWriteChar(value);
			_delay_ms(1000);
		}
	}
}
