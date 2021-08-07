/*************************************************
 * AUTHOR : Moataz
 * Date   : 2/1/2021
 * VERION : V0.0
 * DISCRIPTION: LM_35.c
 **************************************************/
#include "DataTypes.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
void LM35_VoidInit(void)
{
	ADC_VoidInit();
	DIO_voidSetPinDirection(PORT_A, PIN0, INPUT);

}


uint16_t LM35_U16Read(uint8_t Copy_u8readchannel)
{
	uint32_t temp = 0;
	temp = ADC_U16GetChannelReading(Copy_u8readchannel); /* read channel two where the temp sensor is connect */
	temp = (temp*150*5)/(1023*1.5);                      /* calculate the temp from the ADC value*/

	 return temp;
}




