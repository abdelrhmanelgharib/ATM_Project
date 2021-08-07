

#include "DataTypes.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"
#include "UART_int.h"
#include "EEPROM_interface.h"
void eeprom_send_string(uint8_t *str)
{

	uint8_t i = 0, value;
	I2C_MasterStart();
	I2C_SendSlaveAddressWithWrite(0b01010000);
	I2C_WriteDataByte(0b00000001);
	I2C_WriteDataByte(0b00000001);
	while (str[i] != '\0')
	{
		I2C_WriteDataByte(str[i] );
		i++;
	}
	I2C_MasterStop();
}
void eeprom_recieve_string(uint8_t *str)
{

	uint8_t i = 0, value;
	I2C_MasterStart();
	I2C_SendSlaveAddressWithWrite(0b01010000);
	I2C_WriteDataByte(0b00000001);
	I2C_WriteDataByte(0b00000001);

	while (i != 5)
	{
		I2C_MasterStart();
		I2C_SendSlaveAddressWithRead(0b01010000);
		str[i] = I2C_ReadDataByte();
		I2C_MasterStop();
		i++;
	}
	str[i]='\0';
}

uint8_t change_stringToBin(uint8_t *str)
{
	uint32_t num = 0;
	uint32_t bin = 0;
	uint8_t temp = 0;
	uint8_t weight = 1;

	for (uint8_t i = 0; i < 8; i++)
	{
		num = num * 10 + str[i] - '0';
	}

	while (num > 0)
	{
		temp = num % 10;
		num = num / 10;
		bin = bin + temp * weight;
		weight *= 2;
	}
	return bin;
}
