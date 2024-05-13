#include "stm32f10x.h"                  // Device header
#include "USART.h"
#include "MATH.h"

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


float angle_ConversionX(void)
{
	/* 初始化 */
	Serial_Init();
	float Distance = 20;
	float horizontal_Distance = 40;
	float servoX, targetX, RadiusX, output;
	float theta1, theta2, theta3; 
	servoX  = Serial_RxPacket[0];
	targetX = Serial_RxPacket[2];	
	/* END */
	
	/* 运算 */
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
	/* 初始化 */
	Serial_Init();
	float Distance = 20;
	float horizontal_Distance = 40;
	float servoY, targetY, RadiusY, output;
	float theta1, theta2, theta3; 
	servoY  = Serial_RxPacket[1];
	targetY = Serial_RxPacket[3];	
	/* END */
	
	/* 运算 */
	RadiusY = targetY - servoY;		//d, x
	float Horizon = horizontal_Distance + RadiusY;
	theta1 = atan2(Distance, Horizon);
	theta2 = atan2(Distance, horizontal_Distance);
	theta3 = theta1 - theta2;
	output = degreesToRadians(theta3);
	/* END */
	
	return output;
}






