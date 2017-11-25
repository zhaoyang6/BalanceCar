#include "bsp_tim3.h"
#include "bsp_usart1.h"
void Timer_Init(u32 period,u32 prescaler)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
  NVIC_InitTypeDef NVIC_InitStrucuture;
	
	/* 配置TIM3时基函数,每1ms中断一次*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //使能TIM3的时钟
	TIM_TimeBaseStructure.TIM_Period = period;             //技术周期  1000次为一周期
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;           //预分频系数  72MHz/72=1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;          //时钟分割 无
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, DISABLE);                                //此处时钟不打开，在测速时打开以确保计时的准确性
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  //中断优先级设置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStrucuture.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStrucuture.NVIC_IRQChannelPreemptionPriority=2;//设置抢占式优先级
	NVIC_InitStrucuture.NVIC_IRQChannelSubPriority=2;       //设置响应式优先级
	NVIC_InitStrucuture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStrucuture);
}
int ms;
//TIM3中断服务函数
void TIM3_IRQHandler (void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
	ms++;
}
//计时开始函数
void Time_Start(void)
{
	TIM3->CNT=0;    //每次计数都要把计数寄存器清零，以确保每次计数的准确性
	TIM_Cmd(TIM3,ENABLE);//当需要计数时才打开时钟
}
//计时结束函数，返回时间，单位为us
void Time_End(void)
{
  int time=0;  //此变量只是为了承载计数的总时间
	time=(TIM3->CNT+1)+(1000*ms); //时间的单位为us，之所以采用这个单位是想避免小数运算，以提高速度
	TIM_Cmd(TIM3,DISABLE); //计数时钟关闭
	ms=0;
	printf("T=%dus\r\n",time);  	
}
