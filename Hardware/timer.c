//#include "stm32f10x.h"                  // Device header
//#include "ACTION.h"

//void TIM2_Int_Init(uint16_t arr,uint16_t psc)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//��ʱ��2ʹ��
//	TIM_TimeBaseInitStrue.TIM_Period=arr;//����ֵ
//	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//Ԥ��Ƶϵ��
//	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//ģʽ���ϼ���
//	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);
//	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ�ܶ�ʱ��2�����ж�
//	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//��ʱ��2�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;//��ռ���ȼ�1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);	
//	
//	TIM_Cmd(TIM2,ENABLE);//ʹ�ܶ�ʱ��
//	
//}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//�ж��ж�
//	{	
//		Serial_Control();
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//�ֶ�����жϱ�־λ
//	}
//}


