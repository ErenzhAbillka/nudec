#include "stm32f10x.h"  // ���� STM32F10x ϵ��оƬ��ͷ�ļ�

volatile uint8_t isPaused = 0;

void Timer_Init(void) 
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // ���� GPIOB ʱ��

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  // ʹ�� PB0 ��Ϊ��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // ��������Ϊ��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // ���� TIM2 ʱ��

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;  // ����Ԥ��Ƶֵ��72MHz / (7199 + 1) = 10kHz
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 999;  // ��������Ϊ 1000����ʱ������Ϊ 100ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_Cmd(TIM2, ENABLE);  // ʹ�ܶ�ʱ�� TIM2
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // ���� AFIO ʱ��

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);  // �����ⲿ�ж���·

    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;  // ʹ�� EXTI Line 0 ��Ӧ PB0 ����
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;  // �½��ش���
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;  // �ⲿ�ж϶�Ӧ EXTI0
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;  // ��ռ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;         // �����ȼ�
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);


}

void Stop(void) 
{
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);			//�������ڽ������ݵ��ж�
    isPaused = 1;
}

void Resume(void)	
{
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//�������ڽ������ݵ��ж�
    isPaused = 0;
}

void EXTI0_IRQHandler(void) 
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
		{
			EXTI_ClearITPendingBit(EXTI_Line0);  // ����жϱ�־λ
			if (!isPaused)  Stop();  // ִ����ͣ����
			else  		    Resume();  // ִ�лָ�����
    }
}
