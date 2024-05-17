#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "SERIAL.h"
#include "CONTROL.h"
#include "DELAY.h"
#include "PID.h"
#include "USART.h"

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

//float Get_AngleDown(void)
//{
//	float AngleDown = (float)(TIM_GetCapture2(TIM2) - 500) / 2000 * 180;	//得到实时的CCR值
//	return AngleDown;
//}

//float Get_AngleUp(void)
//{
//	float AngleUp 	= (float)(TIM_GetCapture3(TIM2) - 500) / 2000 * 180;	//得到实时的CCR值
//	return AngleUp;
//}

void zhuizongX()
{
	Serial_Init();
	float Angle, Angle_increment;
	int rx  = Serial_RxPacket[0];
	int gx = Serial_RxPacket[2];
	int delta;
	delta = rx - gx;
	
	if(delta > 0) 
	{
		Angle = Get_AngleDown();
		Angle += Angle_increment;
		servoTwoDown(Angle);
	}
	else if(delta < 0) 
	{
		Angle = Get_AngleDown();
		Angle -= Angle_increment;
		servoTwoDown(Angle);
	}
}
	
void zhuizongY()
{
	Serial_Init();
	float Angle, Angle_increment;
	int ry  = Serial_RxPacket[1];
	int gy = Serial_RxPacket[3];
	int delta;
	delta = ry - gy;
	
	if(delta > 0) 
	{
		Angle = Get_AngleDown();
		Angle += Angle_increment;
		servoTwoUp(Angle);
	}
	else if(delta < 0) 
	{
		Angle = Get_AngleDown();
		Angle -= Angle_increment;
		servoTwoUp(Angle);
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
