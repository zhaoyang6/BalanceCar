#include "led.h"
//LED 管脚初始化
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); //GPIOD使能
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14);
	
}

void delay(u32 i)
{
   while(i--); 
}
void LED_Play(void)
{
  GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	delay(6000000);
	GPIO_ResetBits(GPIOD,GPIO_Pin_14);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	delay(6000000);
}
