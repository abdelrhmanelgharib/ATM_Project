/**
 * @file UART.c
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 */

#include "UART_int.h"

static uint8_t *gPsend_str = NULLPTR;
static uint8_t *gPrece_str = NULLPTR, gFlag = 1;

/**
 * @brief Initialized UART 
 * 
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENInit(void)
{
    EN_ERRORSTATE_t Enstate;
    Enstate = E_OK;
    /* Clear  URSEL to update UBRRH*/
    CLRBIT(UCSRC, URSEL);
    /* Boud Rate */
    UBRRH = HIGHUBRR;
    UBRRL = LOWUBRR;

/* UART Double Speed */
#if UART_SPEED == DOUBLE
    SETBIT(UCSRA, U2X);

/* UART NORMAL Speed */
#elif UART_SPEED == NORMAL
    CLRBIT(UCSRA, U2X);
#endif

/* Select STOP Bit */
#if STOPBIT == _1BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    CLRBIT(UCSRC, USBS);

#elif STOPBIT == _2BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    SETBIT(UCSRC, USBS);
#endif

/* Disable Parity */
#if UART_PARITY == DISABLED

    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);

    CLRBIT(UCSRC, UPM0);
    CLRBIT(UCSRC, UPM1);
    /* Parity is Odd */

#elif UART_PARITY == ODD
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    SETBIT(UCSRC, UPM0);
    SETBIT(UCSRC, UPM1);

/* Parity is Even */
#elif UART_PARITY == EVEN
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    CLRBIT(UCSRC, UPM0);
    SETBIT(UCSRC, UPM1);

#endif

/* Data Fram */
#if DATAFRAM == _5BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    CLRBIT(UCSRC, UCSZ0);
    CLRBIT(UCSRC, UCSZ1);
    CLRBIT(UCSRB, UCSZ2);
#elif DATAFRAM == _6BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    SETBIT(UCSRC, UCSZ0);
    CLRBIT(UCSRC, UCSZ1);
    CLRBIT(UCSRB, UCSZ2);
#elif DATAFRAM == _7BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    CLRBIT(UCSRC, UCSZ0);
    SETBIT(UCSRC, UCSZ1);
    CLRBIT(UCSRB, UCSZ2);
#elif DATAFRAM == _8BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    SETBIT(UCSRC, UCSZ0);
    SETBIT(UCSRC, UCSZ1);
    CLRBIT(UCSRB, UCSZ2);
#elif DATAFRAM == _9BIT
    /* Set URSEL to update UCSRC*/
    SETBIT(UCSRC, URSEL);
    SETBIT(UCSRC, UCSZ0);
    SETBIT(UCSRC, UCSZ1);
    SETBIT(UCSRB, UCSZ2);
#else
    Enstate = E_ERROR;
#endif

    /**
     * @brief Receiver Enable
     * 
     */
    SETBIT(UCSRB, RXEN);
    /**
     * @brief Transmitter Enable
     * 
     */
    SETBIT(UCSRB, TXEN);

    return Enstate;
} /* UART_ENInit */

/**
 * @brief Send One Character
 * 
 * @param Data char want to send
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENSendData(uint8_t Data)
{
    /* Wait to Data Register Empty */
    while (!GETBIT(UCSRA, UDRE))
        ;

    UDR = Data;
    return E_OK;
}

/**
 * @brief Send Without Polling On Data Register Flag 
 * 
 * @param Data char want to send
 * @return EN_ERRORSTATE_t E_OK | E_ERROR
 */
EN_ERRORSTATE_t UART_ENSendNoBlock(uint8_t Data)
{
    UDR = Data;
    return E_OK;
}

/**
 * @brief Receive Data From another device
 * 
 * @return uint8_t Data From Register
 */
uint8_t UART_u8ReceiveData(void)
{
    while (!GETBIT(UCSRA, RXC))
        ;
    return UDR;
}

/**
 * @brief Receive Data without Polling
 * 
 * @param Data 
 * @return uint8_t Data From Register
 */
uint8_t UART_u8ReceiveNoBlock(uint8_t *Data)
{
    uint8_t status = 0;
    if (GETBIT(UCSRA, RXC))
    {
        *Data = UDR;
        status = 1;
    }
    else
    {
        /* do nothing */
    }
    return status;
}

/**
 * @brief Enable Transmit Interrupt
 * 
 */
void UART_voidTXInterruptEnable(void)
{
    SETBIT(UCSRB, TXCIE);
    SETBIT(SREG, I_BIT);
}

/**
 * @brief Enable Receive Interrupt
 * 
 */
void UART_voidRXInterruptEnable(void)
{
    SETBIT(UCSRB, RXCIE);
    SETBIT(SREG, I_BIT);
}

/**
 * @brief Asynchronous Function Send 
 * 
 * @param str Data to send
 */
void UART_voidSendString_Ashync(uint8_t *str)
{
    /* Flag using For Protection if call function before string is end */
    if (gFlag == 1)
    {
        /* Send First Letter we bsend b2y fy ISR*/
        UART_ENSendNoBlock(str[0]);

        /* Flag will Fired when data is Sent Then go to isr */
        UART_voidTXInterruptEnable();
        gPsend_str = str;
        gFlag = 0;
    }
}

/**
 * @brief Asynchronous Function Receive 
 * 
 * @param Str Data to Receive
 */
void UART_voidReceiveString_Ashync(uint8_t *Str)
{
    UART_voidRXInterruptEnable();
    gPrece_str = Str;
}

/**
 * @brief Transmit interrupt 
 * 
 */
void __vector_15(void)
{
    /* Start with Second Letter */
    /* First Letter is sent in Function Ashync */
    static uint8_t i = 1;

    if (gPsend_str[i] != '\0')
    {
        UART_ENSendNoBlock(gPsend_str[i]);
        i++;
    }
    /* String is End So start with Second Letter */
    else
    {
        i = 1;
        gFlag = 1;
    }
}

/**
 * @brief Receive interrupt
 * 
 */
void __vector_13(void)
{
    static uint8_t i = 0;
    if (UART_u8ReceiveNoBlock(gPrece_str[i]))
    {
        i++;
    }
    if (i > 98)
        i = 0;
}