

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


typedef enum
{
	STD_TYPES_u8_ERROR_OK,

}EEPROM_Error_States;

uint8_t change_stringToBin(uint8_t*str);
void eeprom_send_string(uint8_t *str,uint8_t address);
void eeprom_recieve_string(uint8_t *str,uint8_t address);

#endif /* EEPROM_INTERFACE_H_ */
