/*************************************************
* AUTHOR : Moataz
* Date   : 2/1/2021
* VERION : V0.0
* DISCRIPTION: ADC_Program
**************************************************/
#include"DataTypes.h"
#include"BIT_MATH.h"
#include"Memmap.h"
#include"ADC_Interface.h"
#include"ADC_Config.h"

void ADC_VoidInit(void)
{

#if ADC_VREF == INTERNAL_OFF
	CLRBIT( ADMUX , 6 ) ;  /*REFS0*/
	CLRBIT( ADMUX , 7 ) ;  /*REFS1*/

#elif ADC_VREF == EXTERNAL_AVCC
	SETBIT( ADMUX , 6 ) ;   /*REFS0*/
	CLRBIT( ADMUX , 7 ) ; /*REFS1*/

#elif ADC_VREF == RESERVED
	CLRBIT( ADMUX , 6 ) ; /*REFS0*/
	SETBIT( ADMUX , 7 ) ;   /*REFS1*/

#elif ADC_VREF == INTERNAL_VOLTAGE
	SETBIT( ADMUX , 6 ) ;   /*REFS0*/
	SETBIT( ADMUX , 7 ) ;   /*REFS1*/

#endif


#if ADC_ADJ	== RIGHT_ADJ
	CLRBIT( ADMUX , 5 ) ; /*ADLAR*/

#elif ADC_ADJ == LEFT_ADJ
	SETBIT( ADMUX , 5 ) ;

#endif


#if ADC_PRESCALER == PRESCALER_2
	SETBIT(ADCSRA, 0);
	CLRBIT(ADCSRA,1);
	CLRBIT(ADCSRA,2);

#elif ADC_PRESCALER == PRESCALER_4
	CLRBIT( ADCSRA , 0 ) ;
	SETBIT( ADCSRA , 1 ) ;
	CLRBIT( ADCSRA , 2 ) ;

#elif ADC_PRESCALER == PRESCALER_8
	SETBIT( ADCSRA , 0 ) ;
	SETBIT( ADCSRA , 1 ) ;
	CLRBIT( ADCSRA , 2 ) ;

#elif ADC_PRESCALER == PRESCALER_16
	CLRBIT( ADCSRA , 0 ) ;
	CLRBIT( ADCSRA , 1 ) ;
	SETBIT( ADCSRA , 2 ) ;

#elif ADC_PRESCALER == PRESCALER_32
	SETBIT( ADCSRA , 0 ) ;
	CLRBIT( ADCSRA , 1 ) ;
	SETBIT( ADCSRA , 2 ) ;

#elif ADC_PRESCALER == PRESCALER_64
	CLRBIT( ADCSRA , 0 ) ;
	SETBIT( ADCSRA , 1 ) ;
	SETBIT( ADCSRA , 2 ) ;

#elif ADC_PRESCALER == PRESCALER_128
	SETBIT( ADCSRA , 0 ) ;
	SETBIT( ADCSRA , 1 ) ;
	SETBIT( ADCSRA , 2 ) ;

#endif
	SETBIT( ADCSRA , 7 ) ;       /*Enable ADC*/
}


uint32_t ADC_U16GetChannelReading(uint8_t Channel)
{
	uint32_t Relult = 0 ;
	ADMUX&= 0XE0 ;                      /*0b11100000*/
	ADMUX |= Channel ;
	SETBIT(ADCSRA,6);                  /* Start Conversion*/
	while(GETBIT(ADCSRA,4)==0);     	/*polling on the conversion complete flag*/
	SETBIT(ADCSRA,4);                  /*CLEAR THE FLAG*/
	Relult = ADC;                       /*get the result*/
	return Relult;
}
