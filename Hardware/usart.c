#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

/****
	* ��OpenMVͨ�ţ�����USART
	* ֡ͷ: 0x2C, 0x04
	* ֡β: 0x5B
	* OpenMV����: cx, cy, dx, dy (c:��ɫ��������, d:��ɫ��������)
	* ��������: PA9: Rx, PA10: Tx
	*/
	
uint8_t flag;							//��־

uint8_t Serial_RxPacket[4];				//����������ݰ�����
uint8_t Serial_RxFlag;					//����������ݰ���־λ

/**
  * ��    �������ڳ�ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Serial_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//����USART1��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA9���ų�ʼ��Ϊ�����������
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA10���ų�ʼ��Ϊ��������
	
	/*USART��ʼ��*/
	USART_InitTypeDef USART_InitStructure;					//����ṹ�����
	USART_InitStructure.USART_BaudRate = 9600;				//������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ�������ƣ�����Ҫ
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//ģʽ������ģʽ�ͽ���ģʽ��ѡ��
	USART_InitStructure.USART_Parity = USART_Parity_No;		//��żУ�飬����Ҫ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ��ѡ��1λ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ���ѡ��8λ
	USART_Init(USART1, &USART_InitStructure);				//���ṹ���������USART_Init������USART1
	
	/*�ж��������*/
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);			//�������ڽ������ݵ��ж�
	
	/*NVIC�жϷ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			//����NVICΪ����2
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStructure;					//����ṹ�����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		//ѡ������NVIC��USART1��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//ָ��NVIC��·ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;		//ָ��NVIC��·����ռ���ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//ָ��NVIC��·����Ӧ���ȼ�Ϊ1
	NVIC_Init(&NVIC_InitStructure);							//���ṹ���������NVIC_Init������NVIC����
	
	/*USARTʹ��*/
	USART_Cmd(USART1, ENABLE);								//ʹ��USART1�����ڿ�ʼ����
}


uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)			//�����־λΪ1
	{
		Serial_RxFlag = 0;
		return 1;					//�򷵻�1�����Զ������־λ
	}
	return 0;						//�����־λΪ0���򷵻�0
}

/**
  * ��    ����USART1�жϺ���
  * ��    ������
  * �� �� ֵ����
  * ע������˺���Ϊ�жϺ�����������ã��жϴ������Զ�ִ��
  *           ������ΪԤ����ָ�����ƣ����Դ������ļ�����
  *           ��ȷ����������ȷ���������κβ��죬�����жϺ��������ܽ���
  */
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;		//�����ʾ��ǰ״̬��״̬�ľ�̬����
	static uint8_t pRxPacket = 0;	//�����ʾ��ǰ��������λ�õľ�̬����
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//�ж��Ƿ���USART1�Ľ����¼��������ж�
	{
		uint8_t RxData = USART_ReceiveData(USART1);				//��ȡ���ݼĴ���������ڽ��յ����ݱ���
		
		/*ʹ��״̬����˼·�����δ������ݰ��Ĳ�ͬ����*/
		
		/*��ǰ״̬Ϊ0���������ݰ���ͷ*/
		if (RxState == 0 && RxData == 0x2C)
		{
				RxState = 1;			//����һ��״̬
				pRxPacket = 0;			//���ݰ���λ�ù���
		}
		else if (RxState == 1 && RxData == 0x04)
		{
				RxState = 2;
		}
		/*��ǰ״̬Ϊ1���������ݰ�����*/
		else if (RxState == 2)
		{
			Serial_RxPacket[pRxPacket] = RxData;	//�����ݴ������ݰ������ָ��λ��
			pRxPacket ++;				//���ݰ���λ������
			if (pRxPacket >= 4)			//����չ�4������
			{
				RxState = 3;			//����һ��״̬
			}
		}
		/*��ǰ״̬Ϊ2���������ݰ���β*/
		else if (RxState == 3 && RxData == 0x5B)
		{
				RxState = 0;			//״̬��0
				Serial_RxFlag = 1;		//�������ݰ���־λ��1���ɹ�����һ�����ݰ�
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//�����־λ
	}
}
