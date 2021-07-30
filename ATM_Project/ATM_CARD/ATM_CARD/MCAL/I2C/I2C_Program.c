/*
 * I2C_program.c
 *
 *  Created on: Dec 28, 2020
 *      Author: Al Badr
 */
#include "DataTypes.h"
#include "BIT_Math.h"
#include "Memmap.h"
#include "I2C_Interface.h"
#include "DIO_Interface.h"

//#include "DIO_Interface.h"

//#include "I2C_Private.h"

//#include <util/delay.h>

void I2C_MasterInit(void){
	// prescaler =1
		CLRBIT(TWSR,0);
		CLRBIT(TWSR,1);
		TWBR=32;//400khz
		//SETBIT(TWCR,6);// enable ACK

		SETBIT(TWCR,2);// enable

		TWAR=0b00000111;



}
void I2C_MasterStart(void){

	SETBIT(TWCR,5);// enable start bit
	SETBIT(TWCR,7);// clear flag

	while(GETBIT(TWCR,7)==0);

}


void I2C_SlaveInit(void){
	TWBR=32;//400khz


	TWAR=0b00000010;
	SETBIT(TWCR,6);// enable ack

	SETBIT(TWCR,2);// enable i2c

	//SETBIT(TWCR,7);// clear flag
	//while(GETBIT(TWCR,7)==0);


	I2C_ReadDataByte();


}

void I2C_SendSlaveAddressWithWrite(uint8_t address){
	TWDR=(address<<1);
	/* Write operation */
		CLRBIT(TWDR,0);
			CLRBIT(TWCR,5);// clear start bit
			SETBIT(TWCR,7);// clear flag
			while(GETBIT(TWCR,7)==0);
}

void I2C_SendSlaveAddressWithRead(uint8_t address){
	TWDR=(address<<1);
	SETBIT(TWDR,0);// read

	CLRBIT(TWCR,5);// clear start bit
	SETBIT(TWCR,7);// clear flag
	while(GETBIT(TWCR,7)==0);
}

void I2C_WriteDataByte(uint8_t data){

TWDR=data;
SETBIT(TWCR,7);// clear flag
while(GETBIT(TWCR,7)==0);

}
uint8_t I2C_ReadDataByte(void){
	uint8_t value;
SETBIT(TWCR,7);// clear flag
while(GETBIT(TWCR,7)==0);

value=TWDR;
return value;
}
void I2C_MasterStop(void){

	SETBIT(TWCR,4);// enable stop bit
	SETBIT(TWCR,2);// enable i2c bit

	SETBIT(TWCR,7);// clear flag



}
