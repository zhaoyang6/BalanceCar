#include "led1.h"
void delay(u32 i)
{
	while(i--);
}
void LED_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStruture;
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStruture.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStruture.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruture.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOD,&GPIO_InitStruture);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14);
}
void LED_Play(void)
{
  GPIO_SetBits(GPIOD,GPIO_Pin_13);
  GPIO_ResetBits(GPIOD,GPIO_Pin_14);
  delay(6000000);
  GPIO_SetBits(GPIOD,GPIO_Pin_14);
  GPIO_ResetBits(GPIOD,GPIO_Pin_13);
  delay(6000000);
}
