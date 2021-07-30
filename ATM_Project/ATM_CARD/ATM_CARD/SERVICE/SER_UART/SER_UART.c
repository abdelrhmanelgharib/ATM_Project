/**
 * @file SER_UART.c
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */

#include "SER_UART_int.h"



/**
 * @brief Send String
 * 
 * @param Str String is sending
 */
void SER_UARTvoidSendString(uint8_t *Str)
{
    uint8_t i = 0;
    for (i = 0; Str[i]; i++)
    {
        UART_ENSendData(Str[i]);
    }
    UART_ENSendData('\r');
}

/**
 * @brief Recevie String
 * 
 * @param Str Store String in Str
 */
void SER_UARTvoidReceiveString(uint8_t *Str)
{
    uint8_t i = 0;
    Str[i] = UART_u8ReceiveData();
    while (Str[i] != '\r')
    {
        i++;
        Str[i] = UART_u8ReceiveData();
    }
    /* replace to NULL */
    Str[i] = 0;
}

/**
 * @brief Receive No Blocking 
 * 
 * @param Str Store String in Str
 */
void SER_UARTvoidReceiveStringNoBLOCKING(uint8_t *Str)
{
    uint8_t i = 0, Data = 0;
    do
    {
        if (UART_u8ReceiveNoBlock(&Data))
        {
            Str[i] = Data;
            i++;
        }
        else
        {
            break;
        }
    } while (Str[i] - 1 != '\r');

    /* replace to NULL */
    Str[i - 1] = '\0';
}

/**
 * @brief Send Number
 * 
 * @param Numb Number
 */
void SER_UARTvoidSendLongNum(uint32_t Numb)
{
    UART_ENSendData((uint8_t)(Numb & 0x000000FF));
    UART_ENSendData((uint8_t)((Numb >> 8) & 0x000000FF));
    UART_ENSendData((uint8_t)((Numb >> 16) & 0x000000FF));
    UART_ENSendData((uint8_t)((Numb >> 24) & 0x000000FF));
}

/**
 * @brief Receive Number
 * 
 * @return Number
 */
uint32_t SER_UARTu32ReceiveLongNum(void)
{
    /* Receive 32Bit divide on 4 Times */
    uint8_t B1 = UART_u8ReceiveData();
    uint8_t B2 = UART_u8ReceiveData();
    uint8_t B3 = UART_u8ReceiveData();
    uint8_t B4 = UART_u8ReceiveData();

    /*  */
    uint32_t u32_Numb = B1 | ((uint32_t)B2 << 8) | ((uint32_t)B3 << 16) | ((uint32_t)B4 << 24);

    return u32_Numb;
}