#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "MATH.h"

/****
	* ������ɫ����ͺ�ɫ������OpenMV�ϵ����ز��,���õ�ʵ�ʵĶ���ǶȲ���
	* ����˵��: degreesToRadians(): �����ƺͽǶ�ֵת������(���ù�
	*			angle_ConversionX(): ������ʵ��ָ�򼤹��Ŀ�꼤��֮��ĽǶȲ���
	* ע������: angle_ConversionX()�е�DistanceΪ����OpenMV��Ŀ��֮��Ĵ�ֱ����, �������غ�ʵ��ֵ��ת������
	*/
	
float degreesToRadians(float rad)
{
    float Angle;
    float pi = 3.141592653;

    Angle = 180 * rad / pi ;
    
    return Angle;
}


float angle_ConversionX(void)
{
	/* ��ʼ�� */
	Serial_Init();
	float Distance = 20;
	float horizontal_Distance = 40;
	float servoX, targetX, RadiusX, output;
	float theta1, theta2, theta3; 
	servoX  = Serial_RxPacket[0];
	targetX = Serial_RxPacket[2];	
	/* END */
	
	/* ���� */
	RadiusX = targetX - servoX;		//d, x
	float Horizon = horizontal_Distance + RadiusX;
	theta1 = atan2(Distance, Horizon);
	theta2 = atan2(Distance, horizontal_Distance);
	theta3 = theta1 - theta2;
	output = degreesToRadians(theta3);
	/* END */
	
	return output;
}

float angle_ConversionY(void)
{
	/* ��ʼ�� */
	Serial_Init();
	float Distance = 20;
	float horizontal_Distance = 40;
	float servoY, targetY, RadiusY, output;
	float theta1, theta2, theta3; 
	servoY  = Serial_RxPacket[1];
	targetY = Serial_RxPacket[3];	
	/* END */
	
	/* ���� */
	RadiusY = targetY - servoY;		//d, x
	float Horizon = horizontal_Distance + RadiusY;
	theta1 = atan2(Distance, Horizon);
	theta2 = atan2(Distance, horizontal_Distance);
	theta3 = theta1 - theta2;
	output = degreesToRadians(theta3);
	/* END */
	
	return output;
}






