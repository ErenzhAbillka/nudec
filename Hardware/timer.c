//#include "stm32f10x.h"                  // Device header
//#include "ACTION.h"

//void TIM2_Int_Init(uint16_t arr,uint16_t psc)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//定时器2使能
//	TIM_TimeBaseInitStrue.TIM_Period=arr;//重载值
//	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//预分频系数
//	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//模式向上计数
//	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能定时器2更新中断
//	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//定时器2中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;//抢占优先级1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	
//	
//	TIM_Cmd(TIM2,ENABLE);//使能定时器
//	
//}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//判断中断
//	{	
//		Serial_Control();
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//手动清除中断标志位
//	}
//}


