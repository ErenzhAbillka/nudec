#include "stdio.h"
#include "SERIAL.h"
#include "OLED.h"
#include "USART.h"
#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "MATHUSE.h"
#include "LASER.h"

int main()
{
	/* 初始化 */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Key_Init();
	Laser_Init();
	/* END */

	/* 常驻外设控制*/
	LASER_ON();
	/* END */
	while(1)
	{
		/* 舵机控制部分 */ 
		float x = PID_Down();
		float y = PID_Up();
		
		Servo_Down(x);
		Servo_Up(y);
		/* END */
		
		/* OLED显示 */
		//EMPTY BODY
		/* END */
	}
	
}

