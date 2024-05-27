/**
<������־>
        time: 5.27	-> Procedure: �߼��ջ�����, �����鴦����
				-> Key: �޸���K3, K4���ν������.
**/
#include "stm32f10x.h"                  // Device header
#include "SERIAL.h"
#include "OLED.h"
#include "USART.h"
#include "KEY.h"
#include "PROCEDURE.h"
#include "DELAY.h"

/*****
	* PB0: ��ʼ�����
	* PB1: ʧ�ܶ��, ��һ�μ�¼һ�κ�ɫ��������ֵ
	*	   �������������ε��ĸ���
	* PB10: ��¼�ĸ����, OLED������֮��, ˳ʱ��ת��
	* PB11: ʶ���ɫ����, ˳ʱ��ת��
	*/

int main()
{
	/* ��ʼ�� */
	Serial_Init();
	OLED_Init();
	PWM_Init();
	Key_Init();

	/* END */

	/* ��פ�������*/
//	Reset();
	/* END */

	while(1)
	{
		OLED_ShowSignedNum(2, 1, Serial_RxPacket[2],3);
		Key_Running();
	}
		
}

