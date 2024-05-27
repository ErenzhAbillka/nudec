#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "USART.h"
#include "SERIAL.h"
#include "DELAY.h"
#include "OLED.h"

/*****
    * ����˵��: Ϊmain��������
    * Reset: ��ʼ�����
    * Servo_Running: ����OpenMV���͵�����,����˳ʱ����Ȧ�˶�
    */

static int theta1;
static int theta2;
static uint8_t Serial_RxPacket[10];  // ȷ�������С��ȷ

void Reset(void)
{
    servoOneDown(128);
    servoOneUp(90);
    // Delay_ms(500);
    // TIM_Cmd(TIM2, DISABLE);
}

void Servo_Running(void)
{
    static int count = 0;  // �� count ����Ϊ��̬����

    // Left -> + Right -> -
    // Up -> + Down -> -
    servoOneDown(128);
    servoOneUp(90);
    
    for (int i = 0; i < 10; i++)
    {
        if (Serial_RxPacket[i] > 127)
        {
            Serial_RxPacket[i] = Serial_RxPacket[i] - 256;
        }
    }
    OLED_ShowSignedNum(4, 1, count, 2);
    if (count == 0)
    {
        theta1 = 128 + Serial_RxPacket[0];  // L
        theta2 = 90 + Serial_RxPacket[1];   // U
        servoOneDown(theta1);
        servoOneUp(theta2);
        count = 1;
	Delay_ms(1000);
    }
    else if (count == 1)
    {
        theta1 = theta1 + Serial_RxPacket[2];  // L
        theta2 = theta2 + Serial_RxPacket[3];  // U
        servoOneDown(theta1);
        servoOneUp(theta2);
        count = 2;
	Delay_ms(1000);
    }
    else if (count == 2)
    {
        theta1 = theta1 + Serial_RxPacket[4];  // L
        theta2 = theta2 + Serial_RxPacket[5];  // U
        servoOneDown(theta1);
        servoOneUp(theta2);
        count = 3;
	Delay_ms(1000);
    }
    else if (count == 3)
    {
        theta1 = theta1 + Serial_RxPacket[6];  // L
        theta2 = theta2 + Serial_RxPacket[7];  // U
        servoOneDown(theta1);
        servoOneUp(theta2);
        count = 4;
	Delay_ms(1000);
    }
    else if (count == 4)
    {
        theta1 = theta1 + Serial_RxPacket[8];  // L
        theta2 = theta2 + Serial_RxPacket[9];  // U
        servoOneDown(theta1);
        servoOneUp(theta2);
        count = 0;
	Delay_ms(1000);
    }
}
