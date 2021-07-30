/**
 * @file DIO_Interface.h
 * @author Elghairb
 * @brief   This a DIO Interface File
 * @version 0.1
 * @date 2021-07-07
 * 
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DataTypes.h"
#include "BIT_Math.h"
#include "Memmap.h"

typedef enum
{
    PORT_A = 0,
    PORT_B ,
    PORT_C ,
    PORT_D

}EN_port_num;

typedef enum
{
    PIN0 = 0,
    PIN1 ,
    PIN2 ,
    PIN3 ,
    PIN4 ,
    PIN5 ,
    PIN6 ,
    PIN7
}EN_pin_num;

typedef enum
{
    INPUT = 0 ,
    OUTPUT ,
    PRTOUTPUT = 0xFF,
    PRTINPUT = 0x00    
}EN_direction_type;

typedef enum
{
    LOW = 0 ,
    HIGH ,
    PRTHIGH = 0xFF,
    PRTLOW = 0
}EN_value_type;



EN_ERRORSTATE_t DIO_voidSetPinValue(EN_port_num EN_Port, EN_pin_num EN_Pin, EN_value_type EN_Value);
EN_ERRORSTATE_t DIO_voidSetPinDirection(EN_port_num EN_port, EN_pin_num EN_Pin, EN_direction_type EN_Direction);
EN_value_type DIO_u8GetPinValue(EN_port_num EN_Port, EN_pin_num EN_Pin);

EN_ERRORSTATE_t DIO_voidTogPin(EN_port_num EN_Port, EN_pin_num EN_Pin);

EN_ERRORSTATE_t DIO_voidSetPortDirection(EN_port_num EN_Port, EN_direction_type EN_Direction);
EN_ERRORSTATE_t DIO_voidSetPortValue(EN_port_num EN_Port, EN_value_type EN_Value);
EN_ERRORSTATE_t DIO_voidInpullUp(EN_port_num EN_Port, EN_pin_num EN_Pin);

#endif /* DIO_INTERFACE_H_ */
