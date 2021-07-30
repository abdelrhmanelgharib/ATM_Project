/******************************************************************************************************
 * File: LCD16x2.h 
 * Author: Khalid Mosaad Zakaria
 * Data: 18 july 2021
 * LCD 4 Bit Mode
 * Description: This File include declaration of APIs List.
*******************************************************************************************************/
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_sendChar(uint8_t data);
void lcd_SetPosition(uint8_t raw, uint8_t column);

void lcd_sendString(uint8_t * data);
void lcd_sendNum( u16 copy_u16number);
void lcd_clear(void);
