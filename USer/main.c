#include "stdio.h"
#include "SERIAL.h"
#include "OLED.h"
#include "USART.h"
#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "MATHUSE.h"
#include "TIMER.h"


int main()
{
	/* 初始化 */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Timer_Init();
	/* END */

	/* 常驻外设控制*/

	/* END */
	while(1)
	{
		OLED_ShowNum(1, 1, Serial_RxPacket[0], 3);
		OLED_ShowNum(2, 1, Serial_RxPacket[1], 3);
//		OLED_ShowNum(3, 1, Serial_RxPacket[2], 3);
//		OLED_ShowNum(4, 1, Serial_RxPacket[3], 3);
	}
	
}

