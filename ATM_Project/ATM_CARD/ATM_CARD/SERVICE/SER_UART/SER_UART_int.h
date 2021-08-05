/**
 * @file SER_UART_int.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */

#ifndef SER_UART_INT_H_
#define SER_UART_INT_H_

#include "../lib/DataTypes.h"
#include "../lib/BIT_Math.h"
#include "../MCAL/UART/UART_int.h"
#include "../lib/Memmap.h"

/**
 * @brief Send String
 * 
 * @param Str String is sending
 */
void SER_UARTvoidSendString(uint8_t *Str);


/**
 * @brief Recevie String
 * 
 * @param Str Store String in Str
 */
void SER_UARTvoidReceiveString(uint8_t *Str);



/**
 * @brief Send Number
 * 
 * @param Numb Number
 */
void SER_UARTvoidSendLongNum(uint32_t Numb);


/**
 * @brief Receive Number
 * 
 * @return Number
 */
uint32_t SER_UARTu32ReceiveLongNum(void);

#endif