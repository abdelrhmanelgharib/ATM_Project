/*
 * APP.h
 *
 *  Created on: Jul 27, 2021
 *      Author: Al Badr
 */

#ifndef ATM_TERMINAL_APP_H_
#define ATM_TERMINAL_APP_H_


void APP_Init(void);
uint8_t ADC_ATM(void);
void ADMIN_Mode(void);
void USER_Mode(void);
uint8_t * Compare_Money(uint32_t Max_money, uint32_t User_money);
void Pass_check(void);
void TEMP(void);
uint8_t String_u8Comp(uint8_t *Str1, uint8_t *Str2);
void Get_Pass(uint8_t *str);
uint32_t String_u8ToNumb(uint8_t *Str);

#endif /* ATM_TERMINAL_APP_H_ */
