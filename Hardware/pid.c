#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "MATHUSE.h"
#include "USART.h"
#include "stdio.h"

/****
	* PID���ƶ��������Χ
	* ˵��: �� MATHUSE.H ���� ERROR( = ������ĽǶȲ�), 
	*		Get_AngleXXXX()�������ص�ǰ�Ƕ�, 
	*		ͨ��PID�㷨���ƶ���ﵽԤ���Ƕ�,������ ERROR ��ֱֵ��0
	* ����ֵ: PID_XXX(): ���Ҫ��ﵽ�ĽǶ�(�����)
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
	float AngleDown = (float)(TIM_GetCapture2(TIM2) - 500) / 2000 * 180;	//�õ�ʵʱ��CCRֵ
	return AngleDown;
}

float Get_AngleUp(void)
{
	float AngleUp 	= (float)(TIM_GetCapture3(TIM2) - 500) / 2000 * 180;	//�õ�ʵʱ��CCRֵ
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
	if(output > 50) output = 50;											//�޷�								 
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
	if(output > 110)  output = 110;									//�޷�
	if(output < 70)	 output = 70;
	return output;
}

