/*
 *  Author: Vicious
 *  Created on: 11/7/2021
 */

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#define RIGHTMOTOR_ON	1
#define RIGHTMOTOR_OFF	0

#define LEFTMOTOR_ON	1
#define LEFTMOTOR_OFF	0

void MOTOR_voidInit(void);
void MOTOR_voidRotateClkWise(uint8_t copy_u8top,uint8_t copy_u8down);
void MOTOR_voidRotateAntiClkWise(uint8_t copy_u8top,uint8_t copy_u8down);
void MOTOR_voidGeneratePWM(uint8_t copy_u8dutycycle);
void MOTOR_voidStop(void);
#endif /* MOTOR_INTERFACE_H_ */
