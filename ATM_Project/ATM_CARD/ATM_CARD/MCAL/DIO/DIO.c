/**
 * @file DIO.c
 * @author Elghairb
 * @brief  This is a DIO File for Atmega32
 * @version 0.1
 * @date 2021-07-07
 * 
 */

#include "DIO_Interface.h"

/**
 * @brief This Function to change Pin value HIGH | LOW
 * 
 * @param EN_Port   PORT Name
 * @param EN_Pin    PIN Number
 * @param EN_Value  HIGH or LOW
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidSetPinValue(EN_port_num EN_Port, EN_pin_num EN_Pin, EN_value_type EN_Value)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    if (EN_Value == LOW)
    {
        switch (EN_Port)
        {
        case PORT_A:
            CLRBIT(PORTA, EN_Pin);
            break;
        case PORT_B:
            CLRBIT(PORTB, EN_Pin);
            break;
        case PORT_C:
            CLRBIT(PORTC, EN_Pin);
            break;
        case PORT_D:
            CLRBIT(PORTD, EN_Pin);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (EN_Value == HIGH)
    {
        switch (EN_Port)
        {
        case PORT_A:
            SETBIT(PORTA, EN_Pin);
            break;
        case PORT_B:
            SETBIT(PORTB, EN_Pin);
            break;
        case PORT_C:
            SETBIT(PORTC, EN_Pin);
            break;
        case PORT_D:
            SETBIT(PORTD, EN_Pin);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    return state;
} /* DIO_voidSetPinValue */


/**
 * @brief This Function to change DIrection of Pins 
 * 
 * @param EN_port PORT Name
 * @param EN_Pin  PIN Number
 * @param EN_Direction Direction of the Pin INPUT | OUTPUT
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidSetPinDirection(EN_port_num EN_port, EN_pin_num EN_Pin, EN_direction_type EN_Direction)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    if (EN_Direction == INPUT)
    {
        switch (EN_port)
        {
        case PORT_A:
            CLRBIT(DDRA, EN_Pin);
            break;
        case PORT_B:
            CLRBIT(DDRB, EN_Pin);
            break;
        case PORT_C:
            CLRBIT(DDRC, EN_Pin);
            break;
        case PORT_D:
            CLRBIT(DDRD, EN_Pin);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    else if (EN_Direction == OUTPUT)
    {
        switch (EN_port)
        {
        case PORT_A:
            SETBIT(DDRA, EN_Pin);
            break;
        case PORT_B:
            SETBIT(DDRB, EN_Pin);
            break;
        case PORT_C:
            SETBIT(DDRC, EN_Pin);
            break;
        case PORT_D:
            SETBIT(DDRD, EN_Pin);
            break;
        default:
            state = E_ERROR;
            break;
        }
    }
    return state;
} /* DIO_voidSetPinDirection */


/**
 * @brief This Function to check value in the pin 
 * 
 * @param EN_Port           PORT Name
 * @param EN_Pin            PIN Number
 * @return EN_value_type    return Pin HIGH | LOW
 */
EN_value_type DIO_u8GetPinValue(EN_port_num EN_Port, EN_pin_num EN_Pin)
{
    EN_value_type EN_ret_val;
    switch (EN_Port)
    {
    case PORT_A:
        EN_ret_val = GETBIT(PINA, EN_Pin);
        break;
    case PORT_B:
        EN_ret_val = GETBIT(PINB, EN_Pin);
        break;
    case PORT_C:
        EN_ret_val = GETBIT(PINC, EN_Pin);
        break;
    case PORT_D:
        EN_ret_val = GETBIT(PIND, EN_Pin);
        break;
    }
    return EN_ret_val;
} /* DIO_u8GetPinValue */


/**
 * @brief This Function to Toggel Pin 
 * 
 * @param EN_Port PORT Name
 * @param EN_Pin PIN Number
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidTogPin(EN_port_num EN_Port, EN_pin_num EN_Pin)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (EN_Port)
    {
    case PORT_A:
        TGLBIT(PORTA, EN_Pin);
        break;
    case PORT_B:
        TGLBIT(PORTB, EN_Pin);
        break;
    case PORT_C:
        TGLBIT(PORTC, EN_Pin);
        break;
    case PORT_D:
        TGLBIT(PORTD, EN_Pin);
        break;
    default:
        state = E_ERROR;
        break;
    }

    return state;
} /* DIO_voidTogPin */


/**
 * @brief This Funtion to Set Value of all Pins in the Port
 * 
 * @param EN_Port PORT Name
 * @param EN_Value HIGH | LOW
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidSetPortValue(EN_port_num EN_Port, EN_value_type EN_Value)
{
    EN_ERRORSTATE_t state;
    state = E_OK;
    switch (EN_Port)
    {
    case PORT_A:
        PORTA = EN_Value;
        break;
    case PORT_B:
        PORTB = EN_Value;
        break;
    case PORT_C:
        PORTC = EN_Value;
        break;
    case PORT_D:
        PORTD = EN_Value;
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
} /* DIO_voidSetPortValue */


/**
 * @brief This Funtion to Set Direction of all Pins in the Port
 * 
 * @param EN_Port PORT Name
 * @param EN_Direction PORT Direction
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidSetPortDirection(EN_port_num EN_Port, EN_direction_type EN_Direction)
{
    EN_ERRORSTATE_t state;
    state = E_OK;

    switch (EN_Port)
    {
    case PORT_A:
        DDRA = EN_Direction;
        break;
    case PORT_B:
        DDRB = EN_Direction;
        break;
    case PORT_C:
        DDRC = EN_Direction;
        break;
    case PORT_D:
        DDRD = EN_Direction;
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;

} /* DIO_voidSetPortDirection */


/**
 * @brief This Function to change pin to Pull Up
 * 
 * @param EN_Port PORT Name
 * @param EN_Pin PIN Number
 * @return EN_ERRORSTATE_t E_OK OR ERROR
 */
EN_ERRORSTATE_t DIO_voidInpullUp(EN_port_num EN_Port, EN_pin_num EN_Pin)
{
    EN_ERRORSTATE_t state;
    state = E_OK;
    switch (EN_Port)
    {
    case PORT_A:
        CLRBIT(DDRA, EN_Pin);
        SETBIT(PORTA, EN_Pin);
        break;
    case PORT_B:
        CLRBIT(DDRB, EN_Pin);
        SETBIT(PORTB, EN_Pin);
        break;
    case PORT_C:
        CLRBIT(DDRC, EN_Pin);
        SETBIT(PORTC, EN_Pin);
        break;
    case PORT_D:
        CLRBIT(DDRD, EN_Pin);
        SETBIT(PORTD, EN_Pin);
        break;
    default:
        state = E_ERROR;
        break;
    }
    return state;
} /* DIO_voidInpullUp */
