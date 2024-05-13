#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "MATHUSE.h"
#include "USART.h"
#include "stdio.h"

/****
	* PID控制舵机浮动范围
	* 说明: 由 MATHUSE.H 传入 ERROR( = 计算出的角度差), 
	*		Get_AngleXXXX()函数返回当前角度, 
	*		通过PID算法控制舵机达到预定角度,即消减 ERROR 的值直到0
	* 返回值: PID_XXX(): 舵机要求达到的角度(有误差)
	*/
	
PID pid;

void PIDX_Init(void)
{
	pid.kp = 1;
	pid.ki = 0.2;
	pid.kd = 2;
	pid.Error = 0;
	pid.Error_Sum = 0;
	pid.Error_Last = 0;
	
	Serial_Init();
	
}

void PIDY_Init(void)
{
	pid.kp = 1;
	pid.ki = 0.2;
	pid.kd = 2;
	pid.Error = 0;
	pid.Error_Sum = 0;
	pid.Error_Last = 0;
	
	Serial_Init();
}

float Get_AngleDown(void)
{
	float AngleDown = (float)(TIM_GetCapture2(TIM2) - 500) / 2000 * 180;	//得到实时的CCR值
	return AngleDown;
}

float Get_AngleUp(void)
{
	float AngleUp 	= (float)(TIM_GetCapture3(TIM2) - 500) / 2000 * 180;	//得到实时的CCR值
	return AngleUp;
}

float PID_Down(void)
{
	PIDX_Init();
	float targetAngleX = angle_ConversionX();
	float Actual = Get_AngleDown();
	float output, theta;
	
	pid.Error = targetAngleX - Actual;
	pid.Error_Sum = pid.Error;
	
	theta = pid.kp * pid.Error
		   + pid.ki * pid.Error_Sum
		   + pid.kp * (pid.Error - pid.Error_Last);
	pid.Error_Last = pid.Error;
	
	output = theta + Actual;
	if(output > 50) output = 50;											//限幅								 
	if(output < 0)	 output = 0;
	return output;
}


float PID_Up(void)
{
	PIDY_Init();
	float targetAngleY = angle_ConversionY();
	float Actual = Get_AngleUp();
	float output, theta;
	
	pid.Error = targetAngleY - Actual;
	pid.Error_Sum = pid.Error;
	
	theta = pid.kp * pid.Error
		   + pid.ki * pid.Error_Sum
		   + pid.kp * (pid.Error - pid.Error_Last);
	pid.Error_Last = pid.Error;
	
	output = theta + Actual;
	if(output > 110)  output = 110;									//限幅
	if(output < 70)	 output = 70;
	return output;
}

