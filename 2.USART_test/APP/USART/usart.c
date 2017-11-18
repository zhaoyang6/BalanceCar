#include "usart.h"

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(UART4,(u8)ch);	
	while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
	return ch;
}
/*
		@功能：串口1初始化
		@管脚：Tx----PA9   Rx----PA10
    @中断优先级：分组1   0 0
    @波特率：9600
*/
void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //波特率设置为9600	//波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
	USART_Init(USART1,&USART_InitStructure);	/* 初始化USART1 */
	USART_Cmd(USART1, ENABLE);		   /* 使能USART1 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
	USART_ClearFlag(USART1,USART_FLAG_TC);//清除USARTx的待处理标志位


	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);
	
}
/*
		@功能：串口2初始化
		@管脚：Tx----PA2   Rx----PA3
    @中断优先级：分组1   0 1
    @波特率：9600
*/
void USART2_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX			   //串口输出PA2
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX			 //串口输入PA3
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //波特率设置为9600	//波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
	USART_Init(USART2,&USART_InitStructure);	/* 初始化USART1 */
	USART_Cmd(USART2, ENABLE);		   /* 使能USART1 */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
	USART_ClearFlag(USART2,USART_FLAG_TC);//清除USARTx的待处理标志位


	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);
}
/*
		@功能：串口3初始化
		@管脚：Tx----PB10   Rx----PB11
    @中断优先级：分组1   0 2
    @波特率：9600
*/
void USART3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOB,&GPIO_InitStructure); /* 初始化GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //波特率设置为9600	//波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
	USART_Init(USART3,&USART_InitStructure);	/* 初始化USART1 */
	USART_Cmd(USART3, ENABLE);		   /* 使能USART1 */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
	USART_ClearFlag(USART3,USART_FLAG_TC);//清除USARTx的待处理标志位


	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);

}
/*
		@功能：串口1初始化
		@管脚：Tx----PC10   Rx----PC11
    @中断优先级：分组1   1 0
    @波特率：9600
*/
void UART4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PC10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PC11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOC,&GPIO_InitStructure); /* 初始化GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //波特率设置为9600	//波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
	USART_Init(UART4,&USART_InitStructure);	/* 初始化USART1 */
	USART_Cmd(UART4, ENABLE);		   /* 使能USART1 */
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
	USART_ClearFlag(UART4,USART_FLAG_TC);//清除USARTx的待处理标志位


	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);
}
/*
		@功能：串口1初始化
		@管脚：Tx----PC12   Rx----PD2
    @中断优先级：分组1   1 1
    @波特率：9600
*/
void UART5_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//声明一个结构体变量，用来初始化GPIO

	USART_InitTypeDef  USART_InitStructure;	  //串口结构体定义

	NVIC_InitTypeDef NVIC_InitStructure;//中断结构体定义
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOD,&GPIO_InitStructure); /* 初始化GPIO */


	USART_InitStructure.USART_BaudRate=9600;   //波特率设置为9600	//波特率
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;		//数据长8位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//1位停止位
	USART_InitStructure.USART_Parity=USART_Parity_No;				//无效验
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //失能硬件流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;	 //开启发送和接受模式
	USART_Init(UART5,&USART_InitStructure);	/* 初始化USART1 */
	USART_Cmd(UART5, ENABLE);		   /* 使能USART1 */
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//使能或者失能指定的USART中断 接收中断
	USART_ClearFlag(UART5,USART_FLAG_TC);//清除USARTx的待处理标志位


	/* 设置NVIC参数 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; 	   //打开USART1的全局中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	 //抢占优先级为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 			//响应优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 			 //使能
	NVIC_Init(&NVIC_InitStructure);
}

/*
   中断服务函数集合
*/
void USART1_IRQHandler(void)	
{
  static u8 k;
	USART_ClearFlag(USART1,USART_FLAG_TC);
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//检查指定的USART中断发生与否	
	{
		k=USART_ReceiveData(USART1);
//		printf("%d\r\n",k);
		USART_SendData(USART1,k);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);	
	}		
}
void USART2_IRQHandler(void)	
{
	static u8 k;
	USART_ClearFlag(USART2,USART_FLAG_TC);
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)//检查指定的USART中断发生与否	
	{
		k=USART_ReceiveData(USART2);
		USART_SendData(USART2,k);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);	
	}
}

void USART3_IRQHandler(void)	
{
	static u8 k;
	USART_ClearFlag(USART3,USART_FLAG_TC);
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)//检查指定的USART中断发生与否	
	{
		k=USART_ReceiveData(USART3);
		USART_SendData(USART3,k);
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	}
}
void UART4_IRQHandler(void)	
{
	static u8 k;
	USART_ClearFlag(USART2,USART_FLAG_TC);
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)//检查指定的USART中断发生与否	
	{
		k=USART_ReceiveData(UART4);
		USART_SendData(UART4,k);
		while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);	
	}
}
void UART5_IRQHandler(void)	
{
	static u8 k;
	USART_ClearFlag(UART5,USART_FLAG_TC);
	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=Bit_RESET)//检查指定的USART中断发生与否
	{
		k=USART_ReceiveData(UART5);
	  k++;	
		USART_SendData(UART5,k);//通过外设USARTx发送单个数据
		while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==Bit_RESET);	
	}
}
