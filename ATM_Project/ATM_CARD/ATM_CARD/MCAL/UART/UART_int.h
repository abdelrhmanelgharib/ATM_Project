/**
 * @file UART_int.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */


#ifndef UART_INT_H_
#define UART_INT_H_

#include "../../lib/DataTypes.h"
#include "../../lib/BIT_Math.h"
#include "UART_config.h"
#include "UART_private.h"

#include "../../lib/Memmap.h"





/**
 * @brief Initialized UART 
 * 
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENInit(void);


/**
 * @brief Send One Character
 * 
 * @param Data char to send
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENSendData(uint8_t Data);


/**
 * @brief Send Without Polling On Data Register Flag 
 * 
 * @param Data char to send
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENSendNoBlock(uint8_t Data);


/**
 * @brief Receive Data From another device
 * 
 * @return uint8_t Data From Register
 */
uint8_t UART_u8ReceiveData(void);


/**
 * @brief Receive Data without Polling
 * 
 * @param Data 
 * @return uint8_t Data From Register
 */
uint8_t UART_u8ReceiveNoBlock(void);



/**
 * @brief Enable Transmit Interrupt
 * 
 */
void UART_voidTXInterruptEnable(void);



/**
 * @brief Enable Receive Interrupt
 * 
 */
void UART_voidRXInterruptEnable(void);

/**
 * @brief Disable Transmit Interrupt
 *
 */
void UART_voidTXInterruptDisable(void);


/**
 * @brief Disable Receive Interrupt
 *
 */
void UART_voidRXInterruptDisable(void);


/**
 * @brief Asynchronous Function Send 
 * 
 * @param str Data to send
 */
void UART_voidSendString_Ashync(uint8_t *str);


/**
 * @brief Asynchronous Function Receive 
 * 
 * @param Str Data to Receive
 */
void UART_voidReceiveString_Ashync(uint8_t *Str);






#endif  /* UART_INT_H_ */

