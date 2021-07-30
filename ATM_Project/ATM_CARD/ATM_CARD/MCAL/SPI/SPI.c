/*
 * SPI.c
 *
 * Created: 7/14/2021 9:16:07 PM
 *  Author: Mohamed
 */ 
#include "DataTypes.h"
#include "SPI_Interface.h"
#include "Memmap.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void SPI_VidInitMaster(void) 
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output 
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	DDRB = DDRB | (1<<PB4);
	DDRB = DDRB | (1<<PB5);
	DDRB = DDRB & ~(1<<PB6);
	DDRB = DDRB | (1<<PB7);
	
	SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_VidInitSlave(void)
{ 
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DDRB = DDRB & (~(1<<PB4));  
	DDRB = DDRB & (~(1<<PB5));
	DDRB = DDRB | (1<<PB6);
	DDRB = DDRB & (~(1<<PB7));
	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_VidSendByte( uint8_t copy_U8Data)
{
	SPDR = copy_U8Data; //send data by SPI
	while (!((SPSR) & (1 << SPIF))); //wait until SPI interrupt flag=1 (data is sent correctly)
}

uint8_t SPI_U8RecieveByte(void)
{
   while (!((SPSR) & (1 << SPIF)));//wait until SPI interrupt flag=1(data is receive correctly)
   return SPDR; //return the received byte from SPI data register
}

void SPI_VidSendString( uint8_t *copy_str)
{
	uint8_t i = 0;

	while(copy_str[i] != '\0')
	{

		SPI_VidSendByte(copy_str[i]);
		i++;

	}
	copy_str[i] = '\r';
	copy_str[i+1] = '\0';

}

void SPI_VidRecieveString(uint8_t *copy_str)
{
	unsigned char i = 0;
	copy_str[i] = SPI_U8RecieveByte();
	while(copy_str[i] != '\r')
	{
		i++;
		copy_str[i] = SPI_U8RecieveByte();
	}
	copy_str[i] = '\0';
}
