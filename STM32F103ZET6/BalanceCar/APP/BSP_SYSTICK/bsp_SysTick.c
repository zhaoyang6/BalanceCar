#include "bsp_SysTick.h"
void Delay_Us(u32 myUs);
void Delay_Ms(u32 myMs);

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Config(SystemCoreClock / 1000))	// ST3.5.0��汾  //1us�ж�
	{ 
		/* Capture error */ 
		while (1);
	}		
//	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;	// �رյδ�ʱ��  
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
//                               whileѭ��ʵ��
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
