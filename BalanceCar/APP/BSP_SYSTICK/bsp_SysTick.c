#include "bsp_SysTick.h"
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0库版本
	{ 
		/* Capture error */ 
		while (1);
	}		
//	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;	// 关闭滴答定时器  
}
//微妙延时
void delay_us(u32 i)
{
	u32 temp;
	SysTick->LOAD=9*i;		 //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		 //使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;		   	 //清零计数器
	do
	{
		temp=SysTick->CTRL;		   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	 //等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}
//毫秒延时
void delay_ms(u32 i)
{
	u32 temp;
	SysTick->LOAD=9000*i;	  //设置重装数值, 72MHZ时
	SysTick->CTRL=0X01;		//使能，减到零是无动作，采用外部时钟源
	SysTick->VAL=0;			//清零计数器
	do
	{
		temp=SysTick->CTRL;	   //读取当前倒计数值
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//等待时间到达
	SysTick->CTRL=0;	//关闭计数器
	SysTick->VAL=0;		//清空计数器
}
