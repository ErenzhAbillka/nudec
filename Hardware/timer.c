#include "stm32f10x.h"  // 包含 STM32F10x 系列芯片的头文件

volatile uint8_t isPaused = 0;

void Timer_Init(void) 
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 开启 GPIOB 时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  // 使用 PB0 作为按键引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // 设置引脚为上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // 开启 TIM2 时钟

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7199;  // 设置预分频值，72MHz / (7199 + 1) = 10kHz
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 999;  // 计数周期为 1000，定时器周期为 100ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_Cmd(TIM2, ENABLE);  // 使能定时器 TIM2
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 开启 AFIO 时钟

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);  // 配置外部中断线路

    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;  // 使用 EXTI Line 0 对应 PB0 引脚
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;  // 下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;  // 外部中断对应 EXTI0
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;  // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;         // 子优先级
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);


}

void Stop(void) 
{
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);			//开启串口接收数据的中断
    isPaused = 1;
}

void Resume(void)	
{
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//开启串口接收数据的中断
    isPaused = 0;
}

void EXTI0_IRQHandler(void) 
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) 
		{
			EXTI_ClearITPendingBit(EXTI_Line0);  // 清除中断标志位
			if (!isPaused)  Stop();  // 执行暂停操作
			else  		    Resume();  // 执行恢复操作
    }
}
