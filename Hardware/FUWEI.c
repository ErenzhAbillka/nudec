#include "stm32f10x.h"                  // Device header
#include "SERIAL.h"



void Zhongduan_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE ); //����gpioʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE ); //����afioʱ��
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode =GPIO_Mode_IPU;//��������
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_12 | GPIO_Pin_1;   //PB12 
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB ,GPIO_PinSource12);   // ����AFIOѡ���ж�����

	EXTI_InitTypeDef        EXTI_InitStructure; 			
	EXTI_InitStructure.EXTI_Line =EXTI_Line12;		//��EXTI�ĵ�1����·���ж�ģʽ
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;			//Ȼ�����ж�
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	//�����жϻ����¼�ģʽ	
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//�����½��ش����������أ�
	EXTI_Init(&EXTI_InitStructure);            //EXTI��ʼ��

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�жϷ��麯�� һ����������һ�ξ���
	
	NVIC_InitTypeDef         NVIC_InitStructre ;
	NVIC_InitStructre.NVIC_IRQChannel=EXTI15_10_IRQn;	//�����ж�ͨ��Ϊ1��EXTIͨ��
	NVIC_InitStructre.NVIC_IRQChannelCmd=ENABLE;    //����ͨ��
	NVIC_InitStructre.NVIC_IRQChannelPreemptionPriority=0; //��ռ���ȼ�
	NVIC_InitStructre.NVIC_IRQChannelSubPriority=0;   //��Ӧ���ȼ���С���ȣ�
	NVIC_Init(&NVIC_InitStructre);  //NVIC��ʼ���������ϼ��У� 

	
}


void  EXTI15_10_IRQHandler(void)   //�����ж���ͣ
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







