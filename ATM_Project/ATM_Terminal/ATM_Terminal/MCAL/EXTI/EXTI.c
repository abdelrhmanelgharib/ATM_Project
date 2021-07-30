/**
 * @file EXTI.c
 * @author Vicious
 * @brief This File for External Interrupts
 * @version 0.1
 * @date 2021-07-10
 * 
 */
#include "EXTI_int.h"


static void (*EXTI_INT0_FPtr)(void) = NULLPTR;
static void (*EXTI_INT1_FPtr)(void) = NULLPTR;
static void (*EXTI_INT2_FPtr)(void) = NULLPTR;

/**
 * @brief Enable External interrupt
 * 
 * @param Interrupt EXTI_INT0 | EXTI_INT1 | EXTI_INT2
 * @return EN_ERRORSTATE_t 
 */
EN_EXTIERRORSTATE_t EXTI_ENEnable(EN_EXTI_t Interrupt)
{
	EN_EXTIERRORSTATE_t state;
	state = E_EXT_OK;

	switch (Interrupt)
	{
	case EXTI_INT0:
		SETBIT(GICR, INT0);
		SETBIT(SREG, I_BIT);
		break;
	case EXTI_INT1:
		SETBIT(GICR, INT1);
		SETBIT(SREG, I_BIT);
		break;
	case EXTI_INT2:
		SETBIT(GICR, INT2);
		SETBIT(SREG, I_BIT);
		break;
	default:
		state = E_EXT_ERROR;
		break;
	}
	return state;
}

EN_EXTIERRORSTATE_t EXTI_ENisable(EN_EXTI_t Interrupt)
{
	EN_EXTIERRORSTATE_t state;
	state = E_EXT_OK;

	switch (Interrupt)
	{
	case EXTI_INT0:
		CLRBIT(GICR, INT0);
		CLRBIT(SREG, I_BIT);
		break;
	case EXTI_INT1:
		CLRBIT(GICR, INT1);
		CLRBIT(SREG, I_BIT);
		break;
	case EXTI_INT2:
		CLRBIT(GICR, INT2);
		CLRBIT(SREG, I_BIT);
		break;
	default:
		state = E_EXT_ERROR;
		break;
	}
	return state;
} /* EXTI_voidDisable */

EN_EXTIERRORSTATE_t EXTI_ENTriggerEdge(EN_EXTI_t Interrupt, EN_TriggerEdge_t Edge)
{
	EN_EXTIERRORSTATE_t state;
	state = E_EXT_OK;

	switch (Interrupt)
	{
	case EXTI_INT0:
		MCUCR &= 0xFC;
		MCUCR |= Edge;
		break;
	case EXTI_INT1:
		switch (Edge)
		{
		case LOW_LEVEL:
			CLRBIT(MCUCR, ISC10);
			CLRBIT(MCUCR, ISC11);
			break;
		case ANY_LOGIC_CHANGE:
			SETBIT(MCUCR, ISC10);
			CLRBIT(MCUCR, ISC11);
			break;
		case FALLING_EDGE:
			CLRBIT(MCUCR, ISC10);
			SETBIT(MCUCR, ISC11);
			break;
		case RISING_EDGE:
			SETBIT(MCUCR, ISC10);
			SETBIT(MCUCR, ISC11);
			break;
		default:
			state = E_EXT_ERROR;
			break;
		}
		break;
	case EXTI_INT2:
		switch (Edge)
		{
		case FALLING_EDGE:
			CLRBIT(MCUCSR, ISC2);
			break;
		case RISING_EDGE:
			SETBIT(MCUCSR, ISC2);
			break;
		default:
			state = E_EXT_ERROR;
			break;
		}
		break;

	default:
		state = E_EXT_ERROR;
		break;
	}
	return state;
} /* EXTI_voidTriggerEdge */

EN_EXTIERRORSTATE_t EXTI_SetCallBack(EN_EXTI_t Interrupt, void (*LocalPtr)(void))
{
	EN_EXTIERRORSTATE_t state;
	state = E_EXT_OK;

	switch (Interrupt)
	{
	case EXTI_INT0:
		EXTI_INT0_FPtr = LocalPtr;
		break;
	case EXTI_INT1:
		EXTI_INT1_FPtr = LocalPtr;
		break;
	case EXTI_INT2:
		EXTI_INT2_FPtr = LocalPtr;
		break;
	default:
		state = E_EXT_ERROR;
		break;
	}
	return state;

} /* EXTI_SetCallBack */

void __vector_1(void)
{
	if (EXTI_INT0_FPtr != NULLPTR)
	{
		EXTI_INT0_FPtr();
	}
}

void __vector_2(void)
{
	if (EXTI_INT1_FPtr != NULLPTR)
	{
		EXTI_INT1_FPtr();
	}
}

void __vector_3(void)
{
	if (EXTI_INT2_FPtr != NULLPTR)
	{
		EXTI_INT2_FPtr();
	}
}
