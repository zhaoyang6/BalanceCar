#include "bsp_SysTick.h"
void Delay_Us(u32 myUs);
void Delay_Ms(u32 myMs);

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0库版本  //1us中断
	{ 
		/* Capture error */ 
		while (1);
	}		
//	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;	// 关闭滴答定时器  
}
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
