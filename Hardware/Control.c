#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "SERIAL.h"
#include "CONTROL.h"
#include "DELAY.h"
#include "PID.h"

/****
	* ���Ƴ���
	* PB0: ׷�ٵ���ͣ��ָ�
	* PB1: ��λ
	* PB10: ִ�л�������
	* PB11: ִ�з��ӳ���
	*/
	
void Reset(void)
{
	PWM_Init();
	servoTwoDown(30);
	servoTwoUp(90);
}

void Control(void)
{
	Key_Init();
	uint8_t KeyNum = Key_GetNum();
	if (KeyNum == 1)
	{
		Reset();
	}
	else if (KeyNum == 2)
	{
		Basic_Task();
	}
	else if (KeyNum == 3)
	{
		Perform_Task();
	}
}


void Basic_Task(void)
{
	
}

void Perform_Task(void)
{
	/* ������Ʋ��� */ 
	float x = PID_Down();
	float y = PID_Up();
	
	servoTwoDown(x);
	servoTwoDown(y);
	/* END */	
}
