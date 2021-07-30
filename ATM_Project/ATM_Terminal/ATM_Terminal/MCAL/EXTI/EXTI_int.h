/**
 * @file EXTI_int.h
 * @author Vicious
 * @brief 
 * @version 0.1
 * @date 2021-07-11
 * 
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_EX_INT_H_
#define MCAL_EXTERNAL_INTERRUPT_EX_INT_H_

#include "DataTypes.h"
#include "BIT_Math.h"
#include "EXTI_private.h"
#include "Memmap.h"

typedef enum
{
    LOW_LEVEL =0,
    ANY_LOGIC_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
}EN_TriggerEdge_t;

typedef enum
{
    EXTI_INT0 = 0,
    EXTI_INT1,
    EXTI_INT2
}EN_EXTI_t;

typedef enum
{
	E_EXT_OK,
	E_EXT_ERROR
}EN_EXTIERRORSTATE_t;

EN_EXTIERRORSTATE_t EXTI_ENEnable(EN_EXTI_t Interrupt);
EN_EXTIERRORSTATE_t EXTI_ENDisable(EN_EXTI_t Interrupt);
EN_EXTIERRORSTATE_t EXTI_ENTriggerEdge(EN_EXTI_t Interrupt, EN_TriggerEdge_t Edge);
EN_EXTIERRORSTATE_t EXTI_SetCallBack(EN_EXTI_t Interrupt, void (*LocalPtr)(void));









#endif
