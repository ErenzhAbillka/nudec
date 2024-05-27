/**
<更新日志>
        time: 5.27	-> Procedure: 逻辑闭环控制, 数据组处理检查
				-> Key: 修复了K3, K4单次进入程序.
**/
#include "stm32f10x.h"                  // Device header
#include "SERIAL.h"
#include "OLED.h"
#include "USART.h"
#include "KEY.h"
#include "PROCEDURE.h"
#include "DELAY.h"

/*****
	* PB0: 初始化舵机
	* PB1: 失能舵机, 按一次记录一次红色激光坐标值
	*	   激光点打在正方形的四个角
	* PB10: 记录四个点后, OLED有数据之后, 顺时针转动
	* PB11: 识别黑色矩形, 顺时针转动
	*/

int main()
{
	/* 初始化 */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Key_Init();

	/* END */

	/* 常驻外设控制*/
//	Reset();
	/* END */

	while(1)
	{
		OLED_ShowSignedNum(2, 1, Serial_RxPacket[2],3);
		Key_Running();
	}
		
}

