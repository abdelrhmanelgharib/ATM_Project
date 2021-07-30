/*
 *  Author: Vicious
 *  Created on: 11/7/2021
 */


#include "DIO_Interface.h"
#include "MOTOR_Config.h"

void MOTOR_voidInit(void){
#if  NUM_OF_MOTORS == CONNECT_TWO_MOTOR
/*INIATE MOTOR ONE ON H-BRIDGE*/
DIO_voidSetPinDirection (MOTOR1_PORT, MOTOR1_PIN1,OUTPUT);
DIO_voidSetPinDirection(MOTOR1_PORT,  MOTOR1_PIN2,OUTPUT);
DIO_voidSetPinDirection(MOTOR1_PORT,MOTOR1_ENABLE,OUTPUT);

/*INIATE MOTOR TWO ON H-BRIDGE*/
DIO_voidSetPinDirection (MOTOR2_PORT, MOTOR2_PIN1,OUTPUT);
DIO_voidSetPinDirection(MOTOR2_PORT,  MOTOR2_PIN2,OUTPUT);
DIO_voidSetPinDirection(MOTOR2_PORT,MOTOR2_ENABLE,OUTPUT);

#elif  NUM_OF_MOTORS ==  CONNECT_ONE_MOTOR
/*INIATE MOTOR ONE ON H-BRIDGE*/
DIO_voidSetPinDirection (MOTOR1_PORT, MOTOR1_PIN1,OUTPUT);
DIO_voidSetPinDirection(MOTOR1_PORT,  MOTOR1_PIN2,OUTPUT);
DIO_voidSetPinDirection(MOTOR1_PORT,MOTOR1_ENABLE,OUTPUT);

#endif
#if MOTOR_STATE ==  MOTOR_Generate_pwm
DIO_voidSetPinDirection (MOTOR_PORT, MOTOR_PIN1,OUTPUT);
DIO_voidSetPinDirection(MOTOR_PORT,  MOTOR_PIN2,OUTPUT);
DIO_voidSetPinDirection(MOTOR_PORT,MOTOR1_ENABLE,OUTPUT);
DIO_voidSetPinValue(MOTOR_PORT, MOTOR_PIN1,HIGH);
DIO_voidSetPinValue(MOTOR_PORT, MOTOR_PIN2,LOW);
#else
#endif
}

void MOTOR_voidRotateClkWise(uint8_t copy_uint8_ttop,uint8_t copy_uint8_tdown){
	if(copy_uint8_ttop == 1){
		/*INIATE MOTOR ONE ON H-BRIDGE*/
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN1,HIGH);
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN2,LOW);
		DIO_voidSetPinValue(MOTOR1_PORT,MOTOR1_ENABLE, HIGH);
	}
	else if(copy_uint8_ttop == 0){
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN2,LOW);
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN2,LOW);
	}
	/*INIATE MOTOR ONE ON H-BRIDGE*/
	if(copy_uint8_tdown== 1){
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN1,HIGH);
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN2,LOW);
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_ENABLE, HIGH);
	}
	else if(copy_uint8_tdown == 0){
		DIO_voidSetPinValue(MOTOR2_PORT, MOTOR2_PIN2,LOW);
		DIO_voidSetPinValue(MOTOR2_PORT, MOTOR2_PIN2,LOW);
	}

}
void MOTOR_voidRotateAntiClkWise(uint8_t copy_uint8_ttop,uint8_t copy_uint8_tdown){
	if (copy_uint8_ttop == 1)
	{
		/*INIATE MOTOR ONE ON H-BRIDGE*/
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN1,LOW);
		DIO_voidSetPinValue(MOTOR1_PORT,  MOTOR1_PIN2,HIGH);
		DIO_voidSetPinValue(MOTOR1_PORT,MOTOR1_ENABLE,HIGH);
	}
	else if(copy_uint8_ttop== 0)
	{
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN1,LOW);
		DIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PIN2,LOW);
	}
		/*INIATE MOTOR ONE ON H-BRIDGE*/
	if(copy_uint8_tdown == 1)
	{
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN1,LOW);
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN2,HIGH);
		DIO_voidSetPinValue(MOTOR2_PORT, MOTOR2_ENABLE,HIGH);
	}


	else if(copy_uint8_tdown == 0 ){
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN1,LOW);
		DIO_voidSetPinValue(MOTOR2_PORT,MOTOR2_PIN2,LOW);
	}


}

void MOTOR_voidStop(void){
	DIO_voidSetPinValue( MOTOR1_PORT,MOTOR1_PIN1,LOW);
	DIO_voidSetPinValue( MOTOR1_PORT,MOTOR1_PIN2,LOW);
	DIO_voidSetPinValue( MOTOR2_PORT,MOTOR2_PIN1,LOW);
	DIO_voidSetPinValue( MOTOR2_PORT,MOTOR2_PIN2,LOW);
	DIO_voidSetPinValue( MOTOR2_PORT,MOTOR2_ENABLE,LOW);
}
