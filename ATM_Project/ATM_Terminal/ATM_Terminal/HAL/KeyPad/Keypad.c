/**
 * @file Keypad.c
 * @author Elgharib
 * @brief KeyPad File
 * @version 0.1
 * @date 2021-07-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "KeyPad_config.h"
#include "KeyPad_int.h"
#include "avr/delay.h"

static uint8_t gKEYPADArr[ROW][COL] = {
    {'1', '2', '3'},
    {'4', '5', '2'},
    {'7', '8', '9'}};

/**
 * @brief Initialize KeyPad Pins
 * 
 */
void KEYPAD_voidInit(void)
{
    DIO_voidInpullUp(KEYPAD_INPORT, KEYPAD_INPUT0);
    DIO_voidInpullUp(KEYPAD_INPORT, KEYPAD_INPUT1);
    DIO_voidInpullUp(KEYPAD_INPORT, KEYPAD_INPUT2);

    DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_OUTPUT0, OUTPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_OUTPUT1, OUTPUT);
    DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_OUTPUT2, OUTPUT);
    // DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_OUTPUT3, OUTPUT);

    DIO_voidSetPinDirection(KEYPAD_INPORT, KEYPAD_INPUT0,INPUT);
    DIO_voidSetPinDirection(KEYPAD_INPORT, KEYPAD_INPUT1,INPUT);
    DIO_voidSetPinDirection(KEYPAD_INPORT, KEYPAD_INPUT2,INPUT);

    DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT0, HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT1, HIGH);
    DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT2, HIGH);
    // DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT3, HIGH);
}

/**
 * @brief Read Pressed Button on KeyPad and Return Key
 * 
 * @return uint8_t Pressed
 */
uint8_t KEYPAD_u8Read(void)
{
    uint8_t i, j, key = DEFAULT_KEY;
    while (1)
    {
        for (i = 0; i < ROW; i++)
        {
            DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT0 + i, LOW);
            for (j = 0; j < COL; j++)
            {
                //key = DEFAULT_KEY;
                if (!DIO_u8GetPinValue(KEYPAD_INPORT, KEYPAD_INPUT0 + j))
                {
                    key = gKEYPADArr[i][j];
                    while (!DIO_u8GetPinValue(KEYPAD_INPORT, KEYPAD_INPUT0 + j))
                        ;
                    // _delay_ms(250);
                }
            }
            DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_OUTPUT0 + i, HIGH);
        }
        return key;
    }
}
