#include "DataTypes.h"
#include "BIT_MATH.h"
#include "APP.h"
#include "UART_int.h"
#include "SPI_Interface.h"
#include "SER_UART_int.h"
#include "SPI_Interface.h"
#include "DIO_Interface.h"


#define STRING_EQUL 0

 uint8_t gFlag = 0;



int main()
{	uint8_t Data[255];
	uint8_t *Admin = "ADMIN";
	uint8_t *User = "USER";
	APP_Init();

//	SPI_VidSendString("USER");






	while (1)
	{
		SER_UARTvoidReceiveString(Data);
		///* Admin
		if (String_u8Comp(Data, Admin) == STRING_EQUL)
		{			gFlag = 0;

			Admin_Mode(Data);
		}
		else if(String_u8Comp(Data, User) == STRING_EQUL)
		{
			gFlag = 1;

			User_Mode(Data);
			if(String_u8Comp(Data, Admin) == STRING_EQUL)
			{
				Admin_Mode(Data);

			}


		}
	}
}









