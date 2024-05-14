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
	/* ��ʼ�� */
//	Serial_Init();
	OLED_Init();
	PWM_Init();
//	Timer_Init();
	/* END */

	/* ��פ�������*/

	/* END */
	while(1)
	{
		Control();
	}
	
}

