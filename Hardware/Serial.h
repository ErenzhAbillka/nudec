#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>
#include "stm32f10x.h"                  // Device header

void PWM_Init(void);

void servoOneDown(float Angle);
void servoOneUp(float Angle);
void servoTwoDown(float Angle);
void servoTwoUp(float Angle);

#endif
