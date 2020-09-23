#include "timer.h"
/*
1.延时函数：
实现delay_us和delay_ms
实现方式：while循环
接口：delay_us和delay_ms（最终调用这两个函数，这两个函数里面会转到所使用的延时方法上去）

2.微秒计时器
用于计算任务调用时间间隔
*/

//内部函数声明
void Delay_Us(u32 myUs);
void Delay_Ms(u32 myMs);

//**************************************************************************
//                         主延时函数
//**************************************************************************
void delay_us(u32 us)
{
	Delay_Us(us);   
}

void delay_ms(u32 ms)
{
	Delay_Ms(ms);   
}



//**********************************************************************************
//                               while循环实现
//**********************************************************************************

void Delay_Us(u32 myUs)   
{
  u32 i;
  while(myUs--)
  {
    i=6;
    while(i--);
  }
}
 
void Delay_Ms(u32 myMs)
{
  u32 i;
  while(myMs--)
  {
    i=7200;
    while(i--);
  }
}

//*************************************************************************************
//	微秒计时器，用于计算代码调用间隔
//*************************************************************************************
void TIM3_init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	/* 配置TIM3时基函数*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, DISABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	/*TIM3溢出中断*/
	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	
	// 设置抢占优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	// 设置子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*开始计时*/
void Time_Start(void)
{
	TIM3 -> CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

/*带返回值停止计时，返回时间值，单位us*/
int ms;
u32 Time_End(void)
{
	int countertime;
	countertime=(TIM3 -> CNT)+(1000*ms);  
	TIM_Cmd(TIM3, DISABLE);
	ms=0;
	return countertime;
}
/*溢出中断服务函数*/
void TIM3_IRQHandler (void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
	ms++;
}
