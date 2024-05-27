#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "USART.h"
#include "PROCEDURE.h"
#include "SERIAL.h"

#define record 9

typedef enum {
    Free,
    State_B0,
    State_B1,
    State_B10,
    State_B11
} KeyState;

KeyState state = Free;

void Key_Init(void)
{
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //开启GPIOB的时钟

    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11 | GPIO_Pin_0 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //将PB1和PB11引脚初始化为上拉输入
	
}

void HandleKeyState(void)
{
    switch (state)
    {
        case State_B0:
           OLED_ShowString(1, 1, "B0");
	    Reset();
            state = Free; // 重置状态为 Free
            break;
        case State_B1:
            OLED_ShowString(1, 1, "B1");
            TIM_Cmd(TIM2, DISABLE);
            USART1_SendByte(9);
            state = Free; // 重置状态为 Free
            break;
        case State_B10:
            OLED_ShowString(1, 1, "B10");
	    for(int i = 0; i <= 5; i++)		Servo_Running();
            state = Free; // 重置状态为 Free
            break;
        case State_B11:
            OLED_ShowString(1, 1, "B11");
            USART1_SendByte(8);
             for(int i = 0; i <= 5; i++)		Servo_Running();
            state = Free; // 重置状态为 Free
            break;
        case Free:
        default:
            break;
    }
}

void Key_Running(void)
{
    if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0 && state == Free) // 0为按下
    {
        Delay_ms(20); // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0); // 等待按键松手
        state = State_B0;
        HandleKeyState();
    }
    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0 && state == Free) // 读PB11输入寄存器的状态，如果为0，则代表按键2按下
    {
        Delay_ms(20); // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0); // 等待按键松手
        state = State_B1;
        HandleKeyState();
    }
    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0 && state == Free) // 0为按下
    {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0); // 等待按键松手
        state = State_B10;
        HandleKeyState();
    }
    else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0 && state == Free) // 读PB11输入寄存器的状态，如果为0，则代表按键2按下
    {
        Delay_ms(20); // 延时消抖
        while (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0); // 等待按键松手
        state = State_B11;
        HandleKeyState();
    }
}


