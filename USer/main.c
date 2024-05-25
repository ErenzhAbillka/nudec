#include "stdio.h"
#include "SERIAL.h"
#include "OLED.h"
#include "USART.h"
#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "MATHUSE.h"
#include "TIMER.h"
#include "KEY.h"
#include "CONTROL.h"



int main()
{
	/* 初始化 */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Key_Init();
//	Timer_Init();
	/* END */

	/* 常驻外设控制*/
	servoOneDown(0);
	servoOneUp(0);
	/* END */

	while(1)
	{
		uint8_t Key = Key_GetNum();
		if(Key == 1)
			{
			USART1_SendByte(8);
			}	
//		servoOneDown(60);
	}	
	
	
}

