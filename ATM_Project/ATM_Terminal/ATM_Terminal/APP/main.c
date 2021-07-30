#include "DataTypes.h"
#include "SER_UART_int.h"
#include "SPI_Interface.h"
#include "APP.h"



/**
 * @brief Compare two string
 * 
 * @param Str1 first string
 * @param Str2 second string
 * @return uint8_t string is equal = 0 or not equal =1 
 */

uint8_t card_gflag=0;
uint8_t gflag=0;

int main()
{
	uint8_t Data[255];
	uint8_t Max_Amount[255];
	uint8_t Dep_money[10];
	uint8_t Card_Pass[10];

	uint8_t i=0;
	uint8_t value=0;

	uint8_t *Admin = "ADMIN";
	uint8_t *User = "USER";
#define STRING_EQUL 0

	APP_Init();


	while (1)
	{
		value=ADC_ATM();
		if(value=='1'){
			TEMP();
		}
		else if(value=='2'){

			SER_UARTvoidSendString("you want ADMIN or USER MODE");
			SER_UARTvoidReceiveString(Data);

			/* Admin */
			if (String_u8Comp(Data, Admin) == STRING_EQUL)
			{
				gflag = 0;

				ADMIN_Mode();

			}
			else if(String_u8Comp(Data, User) == STRING_EQUL)
			{
				gflag = 1;
				SPI_VidSendByte('g');
				uint8_t b1 = SPI_U8RecieveByte();
				//UART_ENSendData(b1);
				SPI_VidSendByte('g');
				card_gflag = SPI_U8RecieveByte();
				UART_ENSendData(card_gflag);

				SER_UARTvoidSendString("waiting for card to insert \r");

			}
		}
	}


}
