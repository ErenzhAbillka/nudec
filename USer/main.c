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
	/* ��ʼ�� */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Key_Init();
	Laser_Init();
	/* END */

	/* ��פ�������*/
	LASER_ON();
	/* END */
	while(1)
	{
		/* ������Ʋ��� */ 
		float x = PID_Down();
		float y = PID_Up();
		
		Servo_Down(x);
		Servo_Up(y);
		/* END */
		
		/* OLED��ʾ */
		//EMPTY BODY
		/* END */
	}
	
}

