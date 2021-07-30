/*
 * APP.c
 *
 *  Created on: Jul 27, 2021
 *      Author: Al Badr
 */


#include "DataTypes.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "UART_int.h"
#include "SER_UART_int.h"
#include "I2C_Interface.h"
#include "EEPROM_interface.h"
#include "LCD16x2.h"
#include "KeyPad_int.h"
#include "EXTI_int.h"
#include "SPI_Interface.h"
#include <util/delay.h>
#include "MOTOR_Interface.h"
#include "ADC_Interface.h"
#include "LM_35_Interface.h"
#include "APP.h"


extern uint8_t card_gflag;

uint8_t *Admin = "ADMIN";
uint8_t *User = "USER";
#define STRING_EQUL 0
uint8_t Max_Amount[255];
uint8_t Data[255];

extern uint8_t gflag;


void EX_Callback(void)
{
	if(gflag == 0||card_gflag=='0')
	{
		SER_UARTvoidSendString("Invalid");
	}else{
		SER_UARTvoidSendString("card and atm is valid");
		USER_Mode();

	}
}
void APP_Init(void){



	UART_ENInit();
	I2C_MasterInit();
	KEYPAD_voidInit();
	lcd_init();
	SPI_VidInitMaster();
	MOTOR_voidInit();
	ADC_VoidInit();
	LM35_VoidInit();
	//SPI_VidRecieveString(Card_Pass);
	DIO_voidSetPinValue(PORT_D,PIN7,HIGH);
	//SER_UARTvoidSendString(Card_Pass);


	DIO_voidSetPinDirection(PORT_D, PIN2, INPUT);
	EXTI_ENEnable(EXTI_INT0);
	EXTI_ENTriggerEdge(EXTI_INT0, FALLING_EDGE);
	EXTI_SetCallBack(EXTI_INT0, EX_Callback);


}



uint8_t ADC_ATM(void){
	uint8_t value=0;


	lcd_clear();
	lcd_sendString("1-Temp");
	lcd_SetPosition(1,0);
	lcd_sendString("2-ATM");

	value=KEYPAD_u8Read();
	while(value==DEFAULT_KEY){
		value=KEYPAD_u8Read();

	}
	return value ;
}

void ADMIN_Mode(void){


	gflag = 0;
	SER_UARTvoidSendString("Enter Password of Admin Mode");
	SER_UARTvoidReceiveString(Data);
	if (String_u8Comp(Data, Admin) == STRING_EQUL){
		SER_UARTvoidSendString("Correct Password");

		SER_UARTvoidSendString("Card Number");
		SER_UARTvoidReceiveString(Data);
		/* Send Card Number To EEPROM */
		eeprom_send_string(Data,0x01);

		/* Send Balance to EEPROM */
		SER_UARTvoidSendString("Enter Balance");
		SER_UARTvoidReceiveString(Data);
		eeprom_send_string(Data,0x01);

		/* Send Max Amount to EEPROM */
	//	SER_UARTvoidSendString("Enter Max Amount");
	//	SER_UARTvoidReceiveString(Max_Amount);
		//eeprom_send_string(Max_Amount,0x10);


	}
	else{
		SER_UARTvoidSendString("Wrong Password ");
		ADC_ATM();
	}
}

void Shift(uint8_t *Str, uint8_t Position, uint8_t End)
{
	uint8_t Temp;
	uint8_t i=0;
	lcd_clear();

	for(i = 1; i<End; i++)
	{
		Temp = Str[5-i];
		Str[5-i-1] = Temp;

	}


}

void USER_Mode(void){
	uint8_t i=0, Temp;
	uint8_t value=0;
	uint8_t Dep_money[5]={0};

	gflag = 1;
	//SPI_VidSendByte('g');
	//uint8_t b1 = SPI_U8RecieveByte();
	//UART_ENSendData(b1);

	Pass_check();
	lcd_clear();
	lcd_sendString("enter deposit amount");
	/*recive the balance of user from eeprom*/
	eeprom_recieve_string(Data,0x01);
	//Data[5]='\0';
	SER_UARTvoidSendString(Data);

	while (i!=4)
	{
		value=KEYPAD_u8Read();
		if(value!=DEFAULT_KEY){

			Dep_money[i]=value;
			lcd_SetPosition(1,1+i);
			lcd_sendChar(value);
			i++;

		}
	}
	Dep_money[i]='\0';
	SER_UARTvoidSendString(Dep_money);
	UART_ENSendData('\r');

	//SER_UARTvoidSendString(Dep_money);
	//i=0;



	UART_ENSendData('\r');
	//eeprom_recieve_string(Max_Amount,0x10);
	//Max_Amount[5]='\0';
	//SER_UARTvoidSendString(Max_Amount);

	uint32_t max_dec=String_u8ToNumb(Max_Amount);
	uint32_t dep_dec=String_u8ToNumb(Dep_money);
	uint32_t bal_dec=String_u8ToNumb(Data);
	lcd_clear();
	lcd_sendNum(max_dec);
	_delay_ms(5000);
	lcd_clear();
	lcd_sendNum(dep_dec);
	_delay_ms(5000);

	lcd_clear();
	lcd_sendNum(bal_dec);
	_delay_ms(5000);
	if(Compare_Money(max_dec,dep_dec)=="invalid"){
		lcd_clear();
		lcd_sendString("invalid: ");
		lcd_SetPosition(1,0);
		lcd_sendString("exceed maxamount");
		_delay_ms(1000);
	}
	else if(Compare_Money(Data,bal_dec)=="invalid"){
		lcd_clear();
		lcd_sendString("invalid: ");
		lcd_SetPosition(1,0);
		lcd_sendString("exceed balance");
		_delay_ms(1000);
	}
	else{
		lcd_clear();
		lcd_sendString("Approved");
		MOTOR_voidRotateClkWise(1,0);
		_delay_ms(1000);
		MOTOR_voidStop();
	}


}

uint8_t * Compare_Money(uint32_t Max_money, uint32_t User_money){

	if (Max_money < User_money)
	{
		return "invalid";
	}
	else
	{
		return "valid";
	}




}

void Pass_check(void){
	uint8_t Pin[5];
	uint8_t i=0;
	uint8_t value;
	uint8_t Card_Pass[5];

	Get_Pass(Card_Pass);


	lcd_clear();
	lcd_sendString("Please Enter PIN");


	while (i!=4){
		value=KEYPAD_u8Read();
		if(value!=DEFAULT_KEY){
			Pin[i]=value;
			lcd_SetPosition(1,1+i);
			lcd_sendChar('*');
			i++;
		}
	}
	Pin[4]='\0';

	SER_UARTvoidSendString(Pin);


	//SER_UARTvoidSendString(Card_Pass);


	lcd_clear();
	lcd_sendString("PASS finished");
	_delay_ms(1000);

	if(String_u8Comp(Pin, Card_Pass) == STRING_EQUL)
	{
		lcd_clear();
		lcd_sendString("PASS Correct");
		_delay_ms(1000);
	}
	else{
		lcd_clear();
		lcd_sendString("PASS incorrect");
		_delay_ms(1000);
		ADC_ATM();
	}




}



void TEMP(void){
	uint8_t value=0;
	value = LM35_U16Read(0);
	lcd_clear();
	lcd_sendString("temp is ");
	_delay_ms(1000);
	lcd_SetPosition(1,0);
	lcd_sendNum(value);
	_delay_ms(5000);
}
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

void Get_Pass(uint8_t *str){

	//SPI_VidSendByte('g');
	//uint8_t b1 = SPI_U8RecieveByte();
	//UART_ENSendData(b1);
	SPI_VidSendByte('g');
	str[0] = SPI_U8RecieveByte();
	UART_ENSendData(str[0]);
	SPI_VidSendByte('g');
	str[1]  = SPI_U8RecieveByte();
	UART_ENSendData(str[1] );
	SPI_VidSendByte('g');
	str[2]  = SPI_U8RecieveByte();
	UART_ENSendData(str[2] );
	SPI_VidSendByte('x');
	str[3]  = SPI_U8RecieveByte();
	UART_ENSendData(str[3] );
	str[4]='\0';
	SER_UARTvoidSendString(str);
}
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
