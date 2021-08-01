/**
 * @file LCD.c
 * @author Elgharib
 * @brief LCD
 * @version 0.1
 * @date 2021-07-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "LCD_Interface.h"

/**
 * @brief Initialize LCD Pins and LCD Mode
 * 
 * Select Mode From Config.h File LCD_enum_8BITS_MODE - LCD_enum_4BITS_MODE
 */
void LCD_voidInit(void)
{
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT, LCD_E_PIN, OUTPUT);

/* 8 Bit Mode  */
#if LCD_CURRENT_MODE == LCD_8BITS_MODE

	/* Set Port as output */
	DIO_voidSetPortDirection(LCD_8BITS_DATA_PORT, PRTOUTPUT);

	/* LCD Init Command */
	_delay_ms(30);
	LCD_voidSendCommand(0x38);
	_delay_ms(1);
	LCD_voidSendCommand(0x0E);
	_delay_ms(1);
	LCD_voidSendCommand(0x01);
	_delay_ms(3);

/* 4 Bit Mode */
#elif LCD_CURRENT_MODE == LCD_4BITS_MODE
	DIO_voidSetPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN1, OUTPUT);
	DIO_voidSetPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN2, OUTPUT);
	DIO_voidSetPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN3, OUTPUT);
	DIO_voidSetPinDirection(LCD_4BITS_PORT, LCD_4BITS_PIN4, OUTPUT);

	_delay_ms(35);
	LCD_voidSendCommand(0x02);
	_delay_ms(1);
	LCD_voidSendCommand(0x28);
	_delay_ms(1);
	LCD_voidSendCommand(0x0E);
	_delay_ms(1);
	LCD_voidSendCommand(0x01);
	_delay_ms(1);
	LCD_voidSendCommand(0x06);
	_delay_ms(3);
#endif
}

/**
 * @brief Send Command to Lcd
 * 
 * @param command Command
 */
void LCD_voidSendCommand(uint8_t command)
{
	_delay_ms(5);
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);

#if LCD_CURRENT_MODE == LCD_8BITS_MODE

	DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, command);

	DIO_voidSetPortValue(PORTA_ID, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPortValue(PORTA_ID, LCD_E_PIN, LOW);

#elif LCD_CURRENT_MODE == LCD_4BITS_MODE

	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN1, GETBIT(command, 4));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN2, GETBIT(command, 5));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN3, GETBIT(command, 6));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN4, GETBIT(command, 7));

	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, LOW);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN1, GETBIT(command, 0));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN2, GETBIT(command, 1));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN3, GETBIT(command, 2));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN4, GETBIT(command, 3));

	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, LOW);

#endif
}

/**
 * @brief Write One Byte On Lcd
 * 
 * @param ch Byte to write
 */
void LCD_voidWriteChar(uint8_t ch)
{
	_delay_ms(5);
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);

#if LCD_CURRENT_MODE == LCD_8BITS_MODE

	DIO_voidSetPortValue(LCD_8BITS_DATA_PORT, ch);

	DIO_voidSetPinValue(PORTA_ID, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(PORTA_ID, LCD_E_PIN, LOW);

#elif LCD_CURRENT_MODE == LCD_4BITS_MODE
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN1, GETBIT(ch, 4));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN2, GETBIT(ch, 5));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN3, GETBIT(ch, 6));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN4, GETBIT(ch, 7));

	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, LOW);

	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN1, GETBIT(ch, 0));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN2, GETBIT(ch, 1));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN3, GETBIT(ch, 2));
	DIO_voidSetPinValue(LCD_4BITS_PORT, LCD_4BITS_PIN4, GETBIT(ch, 3));

	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, LOW);

#endif
}


/**
 * @brief Write String On Lcd
 * 
 * @param str Pointer to The First Element of the String
 */
void LCD_voidWriteString(uint8_t *str)
{
	uint8_t counter = 0;
	while (str[counter] != '\0')
	{
		LCD_voidWriteChar(str[counter]);
		counter++;
	}
}

/**
 * @brief Write Unsigned Integer On Lcd
 * 
 * @param number Unsinged Number
 */
void LCD_voidPrintUnsignedInteger(uint32_t number)
{
	uint8_t Str[16];
	uint8_t count = 0;
	if (number == 0)
	{
		LCD_voidWriteChar('0');
	}
	while (number && (count < 16))
	{
		Str[count++] = number % 10;
		number /= 10;
	}
	while (count)
	{
		LCD_voidWriteChar(Str[--count] + '0');
	}
}

/**
 * @brief Write signed Integer On Lcd
 * 
 * @param number Signed Number
 */
void LCD_voidPrintSignedInteger(sint32_t number)
{
	sint8_t Str[16];
	uint8_t count = 0;
	if (number == 0)
	{
		LCD_voidWriteChar('0');
	}
	while (number < 0)
	{
		LCD_voidWriteChar('-');
		number *= -1;
	}
	while (number && (count < 16))
	{
		Str[count++] = number % 10;
		number /= 10;
	}

	while (count)
	{
		LCD_voidWriteChar(Str[--count] + '0');
	}
}

/**
 * @brief This Function to Control Write On LCD Position
 * 
 * @param raw raw
 * @param col column
 */
void LCD_voidGoto(uint8_t raw, uint8_t col)
{
	switch (raw)
	{
	case 0:
		if ((col < 16) && (col >= 0))
		{
			LCD_voidSendCommand(0x80 + col);
		}
		break;
	case 1:
		if ((col < 16) && (col >= 0))
		{
			LCD_voidSendCommand(0xc0 + col);
		}
		break;
	}
}

/**
 * @brief Clear Lcd
 * 
 */
void LCD_voidCLRDisplay(void)
{
	LCD_voidSendCommand(0x01);
}
