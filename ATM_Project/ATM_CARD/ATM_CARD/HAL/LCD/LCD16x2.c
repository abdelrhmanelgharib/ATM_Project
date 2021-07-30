/******************************************************************************************************
 * File: LCD16x2.c 
 * Author: Khalid Mosaad Zakaria
 * Data: 18 july 2021
 * LCD 4 Bit Mode
 * Description: This File include definitions of APIs List.
*******************************************************************************************************/
#include"DataTypes.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"LCD16x2Config.h"
#include"LCD16x2.h"
#include <util/delay.h>


#define TWO_LINES_5X7_DOT_MATRIX    0x28
#define DISPLAY_ON_CURSOR_OFF       0x0c
#define DISPLAY_CLEAR               0x01
#define INCREMENT_CURSOR            0x06
#define LCD_FIRSTLINE				0x80
#define LCD_SECONDLINE				0xC0

void lcd_init(void)
{
    _delay_ms(40);    
 
    DIO_voidSetPinDirection(LS_PIN,OUTPUT);
    DIO_voidSetPinDirection(EN_PIN,OUTPUT);
    DIO_voidSetPinDirection(R_W_PIN,OUTPUT);	
	_delay_ms(5);	
    DIO_voidSetPortDirection(LCD_DATA_PORT,PRTOUTPUT );

    lcd_command(0x33);
    _delay_ms(2);	
    lcd_command(0x32);    
	_delay_ms(2);
    lcd_command(TWO_LINES_5X7_DOT_MATRIX);
    _delay_ms(2);
    lcd_command(DISPLAY_ON_CURSOR_OFF);
    _delay_ms(2);	
    lcd_command(INCREMENT_CURSOR);
    _delay_ms(2);   	
    lcd_command(DISPLAY_CLEAR);
    _delay_ms(2);
}
void lcd_command(uint8_t cmd)
{
    DIO_voidSetPortValue(LCD_DATA_PORT, (cmd&0xf0));
    DIO_voidSetPinValue(LS_PIN,LOW);
    DIO_voidSetPinValue(R_W_PIN,LOW);    
    DIO_voidSetPinValue(EN_PIN,HIGH);    
    _delay_ms(2);    
    DIO_voidSetPinValue(EN_PIN,LOW);
    _delay_ms(2);     
    DIO_voidSetPortValue(LCD_DATA_PORT, (cmd<<4));
    DIO_voidSetPinValue(EN_PIN,HIGH);  
    _delay_ms(2);   
    DIO_voidSetPinValue(EN_PIN,LOW);
    _delay_ms(2);  
	
    _delay_ms(5); 	 	        
}
void lcd_sendChar(uint8_t data)
{
    DIO_voidSetPortValue(LCD_DATA_PORT,(data&0xf0));
    DIO_voidSetPinValue(LS_PIN,HIGH);
    DIO_voidSetPinValue(R_W_PIN,LOW);    
    DIO_voidSetPinValue(EN_PIN,HIGH);    
    _delay_ms(2);    
    DIO_voidSetPinValue(EN_PIN,LOW);
    _delay_ms(2);     
    DIO_voidSetPortValue(LCD_DATA_PORT, (data<<4));
    DIO_voidSetPinValue(LS_PIN,HIGH);    
	DIO_voidSetPinValue(EN_PIN,HIGH);  
    _delay_ms(2);   
    DIO_voidSetPinValue(EN_PIN,LOW);  
    _delay_ms(2);   	

}
void lcd_sendString(uint8_t * data)
{
	uint8_t i=0;

	while(data[i] != '\0')
	{

		lcd_sendChar(data[i]);
		i++;
	}
}
void lcd_sendNum( u16 copy_u16number)
{

	if (copy_u16number==0)
	{
		lcd_sendChar('0');
	}
	sint8_t i=0;
	uint8_t str_num[5];
	while(copy_u16number>0)
	{
		str_num[i]=copy_u16number%10;
		copy_u16number/=10;
		i++;
	}
	i--;
	while(i>=0)
	{
		switch(str_num[i])
		{
		case 0 : lcd_sendChar('0');break;
		case 1 : lcd_sendChar('1');break;
		case 2 : lcd_sendChar('2');break;
		case 3 : lcd_sendChar('3');break;
		case 4 : lcd_sendChar('4');break;
		case 5 : lcd_sendChar('5');break;
		case 6 : lcd_sendChar('6');break;
		case 7 : lcd_sendChar('7');break;
		case 8 : lcd_sendChar('8');break;
		case 9 : lcd_sendChar('9');break;
		}

		i--;
	}


}

void lcd_SetPosition(uint8_t raw, uint8_t column)
{
	if(0==raw)   
	{
	lcd_command(LCD_FIRSTLINE+column);
	}
	if(1==raw)
	{
	lcd_command(LCD_SECONDLINE+column);                                   
	}

}

void lcd_clear(void)
{
    lcd_command(DISPLAY_CLEAR);
    _delay_ms(2);
}
