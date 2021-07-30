/*
 * SPI_Interface.h
 *
 * Created: 7/14/2021 9:19:36 PM
 *  Author: Mohamed
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


void SPI_VidInitMaster(void);
void SPI_VidInitSlave(void);
void SPI_VidSendByte(const uint8_t copy_U8Data);
uint8_t SPI_U8RecieveByte(void);
void SPI_VidSendString(const uint8_t *copy_str);
void SPI_VidRecieveString(uint8_t *copy_str);



#endif /* SPI_INTERFACE_H_ */