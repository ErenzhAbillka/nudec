#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include <MATH.h>

/****
	* 计算绿色激光和红色激光在OpenMV上的像素差距,并得到实际的舵机角度差异
	* 函数说明: degreesToRadians(): 弧度制和角度值转换函数(不用管
	*			angle_ConversionX(): 计算舵机实际指向激光和目标激光之间的角度差异
	* 注意事项: angle_ConversionX()中的Distance为中心OpenMV与目标之间的垂直距离, 是由像素和实际值的转换而来
	*/
	
float degreesToRadians(float rad)
{
    float Angle;
    float pi = 3.141592653;

    Angle = 180 * rad / pi ;
    
    return Angle;
}


//float angle_ConversionX(void)
//{
//	/* 初始化 */
//	Serial_Init();
//	int redX, greX, deltaR, deltaG;
//	float Distance = 242;									//垂直距离
//	float horizontal_Distance = 97;							//到中心点的水平距离
//	float output;
//	float theta1, theta2, theta3; 
//	redX = Serial_RxPacket[0];								//运动
//	greX = Serial_RxPacket[2];								//追踪
//	/* END */
//	/* 运算 */
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
	/* 初始化 */
	Serial_Init();
	int redY, greY, deltaR, deltaG;
	float Distance = 242;									//垂直距离
	float horizontal_Distance = 97;							//到中心点的水平距离
	float output;
	float theta1, theta2, theta3; 
	redY = Serial_RxPacket[0];								//运动
	greY = Serial_RxPacket[2];								//追踪
	/* END */
	/* 运算 */
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
	
	output = degreesToRadians(theta3);
	return output;
}

float angle_ConversionY(void)
{
	/* 初始化 */
	Serial_Init();
	int redY, greY, deltaR, deltaG;
	float Distance = 242;									//垂直距离
	float horizontal_Distance = 97;							//到中心点的水平距离
	float output;
	float theta1, theta2, theta3; 
	redY = Serial_RxPacket[1];								//运动
	greY = Serial_RxPacket[3];								//追踪
	/* END */
	/* 运算 */
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
	
	output = degreesToRadians(theta3);
	return output;
}






