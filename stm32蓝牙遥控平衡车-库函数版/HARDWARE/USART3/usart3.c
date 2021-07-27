
#include "usart3.h"
u8 Usart3_Receive;
void uart3_init(u32 bound)
	{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);	//使能USART1，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PA端口时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口1 

}


/**************************************************************************
函数功能：串口3接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{	  
	 static	u8 uart_receive;//蓝牙接收相关变量
	 uart_receive=USART3->DR; 

	switch(uart_receive)//SBUF
		 {
             case 'A':          //前进
                               Flag_Qian=1,Flag_Hou=0,Flag_Left=0,Flag_Right=0;//////////////前
                                 break;
						 
             case 'B':          //后退
                               Flag_Qian=0,Flag_Hou=1,Flag_Left=0,Flag_Right=0;//////////////后
                                 break; 
						 
             case 'C':          //左转
                               Flag_Qian=0,Flag_Hou=0,Flag_Left=1,Flag_Right=0;
                                 break; 
						 
             case 'D':          //右转
                               Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=1;
                                 break; 
//						 
//             case 'S':          //停止
//                               Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;
//                                 break;
						 				 
						 
             default:            //未执行任何操作，则处于停止状态
                               Flag_Qian=0,Flag_Hou=0,Flag_Left=0,Flag_Right=0;
                                 break;
         }



	
} 
}

