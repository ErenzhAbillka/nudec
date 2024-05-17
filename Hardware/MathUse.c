#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include <MATH.h>

/****
	* ������ɫ����ͺ�ɫ������OpenMV�ϵ����ز��,���õ�ʵ�ʵĶ���ǶȲ���
	* ����˵��: degreesToRadians(): �����ƺͽǶ�ֵת������(���ù�
	*			angle_ConversionX(): ������ʵ��ָ�򼤹��Ŀ�꼤��֮��ĽǶȲ���
	* ע������: angle_ConversionX()�е�DistanceΪ����OpenMV��Ŀ��֮��Ĵ�ֱ����, �������غ�ʵ��ֵ��ת������
	*/
	
void Serial_Init(void);
	
float radiansToDegrees(float rad)
{

	    float Angle;
		float pi = 3.141592653;

		Angle = 180 * rad / pi ;
    
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//�����־λ
		return Angle;
	

}

float setPointX(void)			//red__cx
{
	Serial_Init();
	int rx = Serial_RxPacket[0];
	
	int distance, delta;
	float setAngle_pi, setAngle_rad;
	distance = 242;
	delta = rx - 160;
	setAngle_rad = atan2(delta, distance);
	setAngle_pi = radiansToDegrees(setAngle_rad);
	
	return delta;
}

float setPointY(void)			//red__cy
{

	int rx = Serial_RxPacket[1];
	
	int distance, delta;
	float setAngle_pi, setAngle_rad;
	distance = 242;
	delta = rx - 120;
	setAngle_rad = atan2(delta, distance);
	setAngle_pi = radiansToDegrees(setAngle_rad);
	
	return setAngle_pi;
}

float measurePointX(void)		//gre__dx
{

	int gx = Serial_RxPacket[2];
	
	int distance, delta;
	float setAngle_pi, setAngle_rad;
	distance = 242;
	delta = gx - 160;
	setAngle_rad = atan2(delta, distance);
	setAngle_pi = radiansToDegrees(setAngle_rad);
	
	return setAngle_pi;
}

float measurePointY(void)		//gre__dy
{

	int gy = Serial_RxPacket[3];
	
	int distance, delta;
	float setAngle_pi, setAngle_rad;
	distance = 242;
	delta = gy - 120;
	setAngle_rad = atan2(delta, distance);
	setAngle_pi = radiansToDegrees(setAngle_rad);
	
	return setAngle_pi;
}

//float angle_ConversionX(void)
//{
//	/* ��ʼ�� */
//	Serial_Init();
//	int redX, greX, deltaR, deltaG;
//	float Distance = 242;									//��ֱ����
//	float horizontal_Distance = 97;							//�����ĵ��ˮƽ����
//	float output;
//	float theta1, theta2, theta3; 
//	redX = Serial_RxPacket[0];								//�˶�
//	greX = Serial_RxPacket[2];								//׷��
//	/* END */
//	/* ���� */
////	RadiusX = targetX - servoX;		//d, x
////	float Horizon = horizontal_Distance + RadiusX;
////	theta1 = atan2(Distance, Horizon);
////	theta2 = atan2(Distance, horizontal_Distance);
////	theta3 = theta1 - theta2;
////	output = degreesToRadians(theta3);
//	/* END */
//	
//	/* theta1: Red */
//	deltaR = redX - 160;
//	float HorizonR = horizontal_Distance + deltaR;
//	theta1 = atan2(Distance, HorizonR);
//	/* END */

//	/* theta2: Gre */
//	deltaG = greX - 160;
//	float HorizonG = horizontal_Distance + deltaG;
//	theta2 = atan2(Distance, HorizonG);
//	/* END */
//	
//	/* theta3: theta1 - theta2*/
//	theta3 = theta1 - theta2;
//	/* END */
//	
//	output = degreesToRadians(theta3);
//	return output;
//}

float angle_ConversionX(void)
{
	/* ��ʼ�� */
	Serial_Init();
	int redY, greY, deltaR, deltaG;
	float Distance = 242;									//��ֱ����
	float horizontal_Distance = 97;							//�����ĵ��ˮƽ����
	float output;
	float theta1, theta2, theta3; 
	redY = Serial_RxPacket[0];								//�˶�
	greY = Serial_RxPacket[2];								//׷��
	/* END */
	/* ���� */
//	RadiusX = targetX - servoX;		//d, x
//	float Horizon = horizontal_Distance + RadiusX;
//	theta1 = atan2(Distance, Horizon);
//	theta2 = atan2(Distance, horizontal_Distance);
//	theta3 = theta1 - theta2;
//	output = degreesToRadians(theta3);
	/* END */
	
	/* theta1: Red */
	deltaR = redY - 160;
	theta1 = atan2(Distance, deltaR);
	/* END */

	/* theta2: Gre */
	deltaG = greY - 160;
	theta2 = atan2(Distance, deltaG);
	/* END */
	
	/* theta3: theta1 - theta2*/
	theta3 = theta1 - theta2;
	/* END */
	
	output = radiansToDegrees(theta3);
	return output;
}

float angle_ConversionY(void)
{
	/* ��ʼ�� */
	Serial_Init();
	int redY, greY, deltaR, deltaG;
	float Distance = 242;									//��ֱ����
	float horizontal_Distance = 97;							//�����ĵ��ˮƽ����
	float output;
	float theta1, theta2, theta3; 
	redY = Serial_RxPacket[1];								//�˶�
	greY = Serial_RxPacket[3];								//׷��
	/* END */
	/* ���� */
//	RadiusX = targetX - servoX;		//d, x
//	float Horizon = horizontal_Distance + RadiusX;
//	theta1 = atan2(Distance, Horizon);
//	theta2 = atan2(Distance, horizontal_Distance);
//	theta3 = theta1 - theta2;
//	output = degreesToRadians(theta3);
	/* END */
	
	/* theta1: Red */
	deltaR = redY - 120;
	theta1 = atan2(Distance, deltaR);
	/* END */

	/* theta2: Gre */
	deltaG = greY - 120;
	theta2 = atan2(Distance, deltaG);
	/* END */
	
	/* theta3: theta1 - theta2*/
	theta3 = theta1 - theta2;
	/* END */
	
	output = radiansToDegrees(theta3);
	return output;
}






