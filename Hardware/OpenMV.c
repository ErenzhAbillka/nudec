//#include "stm32f10x.h"  // 包含你的STM32系列的头文件

//uint8_t flag;
//static uint8_t coordinate[4];
////uint8_t coordinate_x = 0;
////uint8_t coordinate_y = 0;
////uint8_t coordinate_w = 0;
////uint8_t coordinate_h = 0;


//void Openmv_Receive_Data(int16_t data);  // 函数声明

//void USART1_IRQHandler(void)
//{
//    uint8_t res;
//    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//    {
//        res = USART_ReceiveData(USART1);
//        Openmv_Receive_Data(res);
//        flag = 1;
//        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//    }
//}

//void Openmv_Receive_Data(int16_t data)
//{
//	static uint8_t state = 0;
//	static uint8_t time = 0;


//	   if (state == 0 && data == 0x2C)	state = 1;
//		   
//	   else if(state == 1 && data == 0x04)	 state = 2;
//		  
//	   else if(state == 2)
//	   {
//		   coordinate[time++] = data;
//		   if (time == 2)
//		   {
////			 coordinate_x = coordinate[0];
////			 coordinate_y = coordinate[1];
//			state = 3;
//			time = 0;
//		   }
//	   }
//	   else if (state == 3 && data == 0x5B)	state = 0;
//	
//}
//	
