/**
 * @file UART_config.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*
    DOUBLE - NORMAL
*/
#define UART_SPEED  NORMAL


/*
    DISABLED - EVEN - ODD
*/
#define UART_PARITY  DISABLED

/*
    _5BIT - _6BIT - _7BIT - _8BIT 
 */
#define DATAFRAM    _8BIT


/*
    1_BIT - _2BIT
 */
#define STOPBIT        _1BIT

/* 
   UBRR Setting 
   8MHz, 9600 BaudRate 
*/
#define HIGHUBRR         0
#define LOWUBRR          51



#endif  /* UART_CONFIG_H_ */