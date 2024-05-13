#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);
void Stop(void);
void Resume(void);
void EXTI0_IRQHandler(void);

#endif
