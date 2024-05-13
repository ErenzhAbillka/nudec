#ifndef __USART_H
#define __USART_H

#include <stdio.h>

extern uint8_t Serial_RxPacket[];

void Serial_Init(void);
uint8_t Serial_GetRxFlag(void);
void USART1_IRQHandler(void);


#endif
