#include "stm32f10x.h"                  // Device header

void WORDDMA_Init(uint32_t addrA, uint32_t addrB, uint16_t Size)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_Initsturcture;
	DMA_Initsturcture.DMA_BufferSize = Size;//�����������
	DMA_Initsturcture.DMA_DIR = DMA_DIR_PeripheralSRC;//������ΪԴͷ����Ĵ���
	DMA_Initsturcture.DMA_M2M = DMA_M2M_Enable;//�������
	DMA_Initsturcture.DMA_MemoryBaseAddr = addrB;
	DMA_Initsturcture.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Initsturcture.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Initsturcture.DMA_Mode = DMA_Mode_Normal;//�Զ���װ��//Normal���Զ���װ
	DMA_Initsturcture.DMA_PeripheralBaseAddr = addrA;//�������ַ
	DMA_Initsturcture.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//SIZEΪ�ֽڵ���ʽ
	DMA_Initsturcture.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//��ַ����
	DMA_Initsturcture.DMA_Priority = DMA_Priority_Medium;//���ȼ�
	DMA_Init(DMA1_Channel1, &DMA_Initsturcture);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
