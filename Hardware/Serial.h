#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include "stm32f10x.h"                  // Device header

extern uint8_t Serial_RxPacket[];
void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);
void Servo_Down(float Angle);
void Servo_Up(float Angle);
float Get_AngleUp(void);
float Get_AngleDown(void);
	
void Control_test(void);

#endif
