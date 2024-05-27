#include "stm32f10x.h"                  // Device header
#include "SERIAL.h"



void Zhongduan_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE ); //开启gpio时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE ); //开启afio时钟
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU;//上拉输入
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_12 | GPIO_Pin_1;   //PB12 
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB ,GPIO_PinSource12);   // 配置AFIO选择中断引脚

	EXTI_InitTypeDef        EXTI_InitStructure; 			
	EXTI_InitStructure.EXTI_Line =EXTI_Line12;		//将EXTI的第1个线路配中断模式
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;			//然后开启中断
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	//配置中断还是事件模式	
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//配置下降沿触发（上升沿）
	EXTI_Init(&EXTI_InitStructure);            //EXTI初始化

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断分组函数 一个工程设置一次就行
	
	NVIC_InitTypeDef         NVIC_InitStructre ;
	NVIC_InitStructre.NVIC_IRQChannel=EXTI15_10_IRQn;	//设置中断通道为1的EXTI通道
	NVIC_InitStructre.NVIC_IRQChannelCmd=ENABLE;    //开启通道
	NVIC_InitStructre.NVIC_IRQChannelPreemptionPriority=0; //抢占优先级
	NVIC_InitStructre.NVIC_IRQChannelSubPriority=0;   //响应优先级（小的先）
	NVIC_Init(&NVIC_InitStructre);  //NVIC初始化，（及上几行） 

	
}


void  EXTI15_10_IRQHandler(void)   //按键中断暂停
{
	if(EXTI_GetITStatus(EXTI_Line12)==SET)
	{
		while(1)
		{

			EXTI_ClearITPendingBit(EXTI_Line12);
			servoOneDown(128);
			servoOneUp(105);
						

		}
	}
		
	

}







