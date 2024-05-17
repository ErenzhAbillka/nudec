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
//	Timer_Init();
	/* END */

	/* 常驻外设控制*/
	servoOneDown(0);
	servoOneUp(0);
	/* END */

	while(1)
	{
		float x = IncrementalPIDX();
		float y = IncrementalPIDY();
		
		int a = measurePointX();
		int b = measurePointY();
		servoOneDown(x);
		servoOneUp(y);
		
		OLED_ShowNum(1, 1, Serial_RxPacket[0], 3);
		OLED_ShowNum(2, 1, Serial_RxPacket[1], 3);
		OLED_ShowNum(3, 1, Serial_RxPacket[2], 3);
		OLED_ShowNum(4, 1, Serial_RxPacket[3], 3);
		
		OLED_ShowNum(1, 5, x, 3);
		OLED_ShowNum(2, 5, y, 3);
		OLED_ShowNum(3, 5, a, 3);
		OLED_ShowNum(4, 5, b, 3);
		
		
	}
	
}

