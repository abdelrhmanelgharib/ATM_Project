/**
 * @file UART_private.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*
    UART SPEED
 */
#define NORMAL      0
#define DOUBLE      1


/*
    PARITY MODE
 */ 
#define DISABLED    0
#define ODD         1
#define EVEN        2

#define _5BIT       1
#define _6BIT       2
#define _7BIT       3
#define _8BIT       4
#define _9BIT       5

/* Receive Complete */
void __vector_13(void) __attribute__((signal));


/* Data Register Empty */
void __vector_14(void) __attribute__((signal));

/* Transmit Complete */
void __vector_15(void) __attribute__((signal));


#endif  /* UART_PRIVATE_H_ */