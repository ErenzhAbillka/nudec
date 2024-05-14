#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "SERIAL.h"
#include "CONTROL.h"
#include "DELAY.h"
#include "PID.h"

/****
	* 控制程序
	* PB0: 追踪的暂停与恢复
	* PB1: 复位
	* PB10: 执行基本程序
	* PB11: 执行发挥程序
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
	/* 舵机控制部分 */ 
	float x = PID_Down();
	float y = PID_Up();
	
	servoTwoDown(x);
	servoTwoDown(y);
	/* END */	
}
