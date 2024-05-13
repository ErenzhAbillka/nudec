#include "stm32f10x.h"                  // Device header

void WORDDMA_Init(uint32_t addrA, uint32_t addrB, uint16_t Size)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_Initsturcture;
	DMA_Initsturcture.DMA_BufferSize = Size;//传输的数据量
	DMA_Initsturcture.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为源头传向寄存器
	DMA_Initsturcture.DMA_M2M = DMA_M2M_Enable;//软件触发
	DMA_Initsturcture.DMA_MemoryBaseAddr = addrB;
	DMA_Initsturcture.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Initsturcture.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Initsturcture.DMA_Mode = DMA_Mode_Normal;//自动重装器//Normal不自动重装
	DMA_Initsturcture.DMA_PeripheralBaseAddr = addrA;//外设基地址
	DMA_Initsturcture.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//SIZE为字节的形式
	DMA_Initsturcture.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//地址自增
	DMA_Initsturcture.DMA_Priority = DMA_Priority_Medium;//优先级
	DMA_Init(DMA1_Channel1, &DMA_Initsturcture);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
