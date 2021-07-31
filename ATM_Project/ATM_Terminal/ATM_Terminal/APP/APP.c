/**
 * @file APP.c
 * @author Vicious
 * @brief Source File
 * @version 0.1
 * @date 2021-07-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "APP.h"

/***************************Global Var********************************/
extern volatile uint8_t card_gflag;
uint8_t Max_Amount[50] = {1, 1, 1, 1};
volatile uint8_t CallBackFLag = 0;
extern uint8_t gflag;
/*******************************************************************/

/**
 * @brief Call Back Function 
 * 
 */
void EX_Callback(void)
{
	if (gflag == 0 || card_gflag == '0')
	{
		SER_UARTvoidSendString((uint8_t *)"Invalid");
	}
	else
	{
		SER_UARTvoidSendString((uint8_t *)"card and atm is valid");
		CallBackFLag = VALID;
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
	KEYPAD_voidInit();
	lcd_init();
	SPI_VidInitMaster();
	MOTOR_voidInit();
	ADC_VoidInit();
	LM35_VoidInit();

	/* Set Direction for EXTI */
	DIO_voidSetPinDirection(PORT_D, PIN2, INPUT);
	DIO_voidInpullUp(PORT_D, PIN2);
	EXTI_ENEnable(EXTI_INT0);
	EXTI_ENTriggerEdge(EXTI_INT0, FALLING_EDGE);
	EXTI_SetCallBack(EXTI_INT0, EX_Callback);
}

/**
 * @brief Home Screen for ATM ask for ATM OR Temperature
 * 
 * @return uint8_t keypad Pressed Value
 */
uint8_t ADC_ATM(void)
{
	uint8_t value = 0;
	/* CLR LCD */
	lcd_clear();

	lcd_sendString((uint8_t *)"1-Temp");
	lcd_SetPosition(1, 0);
	lcd_sendString((uint8_t *)"2-ATM");

	value = KEYPAD_u8Read();
	while (value == DEFAULT_KEY)
	{

		value = KEYPAD_u8Read();
	}
	return value;
}

/**
 * @brief This function for Admin Mode to store data on eeprom and enter new number, balance and MaxAmount 
 * 
 */
void ADMIN_Mode(void)
{
	uint8_t *Admin = (uint8_t *)"ADMIN";
	/* used for take password, card number and balance */
	uint8_t Data[55] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

	gflag = 0;
	SER_UARTvoidSendString((uint8_t *)"Enter Password of Admin Mode: ");
	SER_UARTvoidReceiveString(Data);
	if (String_u8Comp(Data, Admin) == STRING_EQUL)
	{
		SER_UARTvoidSendString((uint8_t *)"Correct Password");
		SER_UARTvoidSendString((uint8_t *)"Card Number : ");
		SER_UARTvoidReceiveString(Data);
		/* Send Card Number To EEPROM */
		eeprom_send_string(Data, 0x01);

		/* Send Balance to EEPROM */
		SER_UARTvoidSendString((uint8_t *)"Enter Balance: ");
		SER_UARTvoidReceiveString(Data);
		eeprom_send_string(Data, 0xB1);

		/* Send Max Amount to EEPROM */
		SER_UARTvoidSendString((uint8_t *)"Enter Max Amount: ");
		SER_UARTvoidReceiveString(Max_Amount);
		eeprom_send_string(Max_Amount, 0xF3);
	}
	else
	{
		SER_UARTvoidSendString((uint8_t *)"Wrong Password ");
		ADC_ATM();
	}
}

/**
 * @brief This Function For user Mode to check user password and deposit and turn on motor if Approved
 * 
 */
void USER_Mode(void)
{
	uint8_t i = 0;
	uint8_t value = 0;
	uint8_t Dep_money[5] = {1, 1, 1, 1};
	uint8_t Temp[255] = {1, 1, 1, 1, 1};
	static volatile uint8_t Card_Pass[5] = {1, 1, 1, 1};
	static uint8_t Flag = 3;

	gflag = 1;
	switch (Flag)
	{
	case 3:
		Get_Pass(Card_Pass);
		Flag = 5;
		break;
	default:
		break;
	}

	if (Pass_check(Card_Pass))
	{

		lcd_clear();
		lcd_sendString((uint8_t *)"enter deposit amount");
		/*receive the balance of user from eeprom*/
		eeprom_recieve_string(Temp, 0xB1);

		while (i != 4)
		{
			value = KEYPAD_u8Read();
			if (value != DEFAULT_KEY)
			{

				Dep_money[i] = value;
				lcd_SetPosition(1, 1 + i);
				lcd_sendChar(value);
				i++;
			}
		}
		Dep_money[i] = '\0';

		eeprom_recieve_string(Max_Amount, 0xF3);

		uint32_t max_dec = String_u8ToNumb(Max_Amount);
		uint32_t dep_dec = String_u8ToNumb(Dep_money);
		uint32_t bal_dec = String_u8ToNumb(Temp);

		if (Compare_Money(max_dec, dep_dec) == INVALID)
		{
			lcd_clear();
			lcd_sendString((uint8_t *)"invalid: ");
			lcd_SetPosition(1, 0);
			lcd_sendString((uint8_t *)"exceed maxamount");
			_delay_ms(1000);
		}
		else if (Compare_Money(bal_dec, dep_dec) == INVALID)
		{
			lcd_clear();
			lcd_sendString((uint8_t *)"invalid: ");
			lcd_SetPosition(1, 0);
			lcd_sendString((uint8_t *)"exceed balance");
			_delay_ms(1000);
		}
		else
		{
			lcd_clear();
			lcd_sendString((uint8_t *)"Approved");
			MOTOR_voidRotateClkWise(1, 0);
			_delay_ms(1000);
			MOTOR_voidStop();
		}
	}
}

/**
 * @brief compare user enter money and balance
 * 
 * @param Max_money MAX AMOUNT Cal withdraw
 * @param User_money Deposit 
 * @return uint8_t* VALID | INVALID
 */
uint8_t Compare_Money(uint32_t Max_money, uint32_t User_money)
{

	if (Max_money < User_money)
	{
		return INVALID;
	}
	else
	{
		return VALID;
	}
}

/**
 * @brief Check for Passwrod 
 * 
 * @param Card_Pass store passwrod on Card_Pass
 * @return uint8_t CORRECT | INCORRECT
 */
uint8_t Pass_check(uint8_t *Card_Pass)
{
	uint8_t Pin[5];
	uint8_t i = 0;
	uint8_t value;

	uint8_t Flag = 0;

	lcd_clear();
	lcd_sendString((uint8_t *)"Please Enter PIN");

	while (i != 4)
	{
		value = KEYPAD_u8Read();
		if (value != DEFAULT_KEY)
		{
			Pin[i] = value;
			lcd_SetPosition(1, 1 + i);
			lcd_sendChar('*');
			i++;
		}
	}
	Pin[4] = '\0';

	lcd_clear();
	lcd_sendString((uint8_t *)"PASS finished");
	_delay_ms(1000);

	if (String_u8Comp(Pin, Card_Pass) == STRING_EQUL)
	{
		lcd_clear();
		lcd_sendString((uint8_t *)"PASS Correct");
		Flag = CORRECT;
		_delay_ms(1000);
	}
	else
	{
		lcd_clear();
		lcd_sendString((uint8_t *)"PASS incorrect");
		Flag = INCORRECT;
		_delay_ms(1000);
	}

	return Flag;
}

/**
 * @brief Display Temp on Lcd if user select Temp Mode
 * 
 */
void TEMP(void)
{
	uint8_t value = 0;
	value = LM35_U16Read(0);
	lcd_clear();
	lcd_sendString((uint8_t *)"temp is ");
	_delay_ms(1000);
	lcd_SetPosition(1, 0);
	lcd_sendNum(value);
	_delay_ms(3000);
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

/**
 * @brief send garbag value to slave to receive his own data
 * 
 * @param str receive data form slave
 */
void Get_Pass(uint8_t *str)
{
	SPI_VidSendByte('g');
	str[0] = SPI_U8RecieveByte();
	SPI_VidSendByte('g');
	str[1] = SPI_U8RecieveByte();
	SPI_VidSendByte('g');
	str[2] = SPI_U8RecieveByte();
	SPI_VidSendByte('x');
	str[3] = SPI_U8RecieveByte();
	str[4] = '\0';
}

/**
 * @brief Convert String to Number 
 * 
 * @param Str Pointer to the first element in the array
 * @return uint32_t Number after Converted to Real Numb
 */
uint32_t String_u8ToNumb(uint8_t *Str)
{
	uint8_t i;
	uint32_t Result = 0;
	for (i = 0; Str[i]; i++)
	{
		Result = Result * 10 + Str[i] - '0';
	}
	return Result;
}
