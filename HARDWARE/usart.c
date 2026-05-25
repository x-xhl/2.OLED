#include "stm32f10x.h"

/*********************************************************************************************
* 名称：usart_init
* 功能：usart1初始化
* 参数：bound波特率
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void usart_init(unsigned int bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     	//使能GPIOB时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);    	//使能USART3时钟 
  
  //USART3端口配置
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    
  GPIO_Init(GPIOB,&GPIO_InitStructure);  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		 
  GPIO_Init(GPIOB,&GPIO_InitStructure); 
  //USART3 初始化设置
  USART_InitStructure.USART_BaudRate = bound;                   //波特率设置
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //字长为8位数据格式
  USART_InitStructure.USART_StopBits = USART_StopBits_1;        //一个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No;           //无奇偶校验位
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
  //收发模式
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);                     //根据上述配置初始化串口1	
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             //串口1中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;       //抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	        //子优先级1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	        //IRQ通道使能
  NVIC_Init(&NVIC_InitStructure);	                        //根据指定的参数初始化VIC寄存器、
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                //开启串口1接收中断
  USART_Cmd(USART3, ENABLE);                                    //使能串口1 	
}

/*********************************************************************************************
* 名称：USART3_IRQHandler
* 功能：串口中断处理函数
* 参数：无
* 返回：无
* 修改：
* 注释：
*********************************************************************************************/
void USART3_IRQHandler(void)                	           
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){        //如果收到数据(接收中断) 
    USART_ClearFlag(USART3, USART_IT_RXNE);                     //清除接收中断标志     
  } 
}
