#include "bsp_motor.h"
/*
@功能：电机驱动板初始化
@管脚：转向控制：左电机PC4 PC5  右电机 PC6 PC7
       使能控制 PC8
*/
void Motor_Drive_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
		
	GPIO_SetBits(GPIOC,GPIO_Pin_8);  //驱动板使能
	
}
/*
 @功能：PWM输出初始化
 @管脚：PA6(TIM3_CH1) PA7(TIM3_CH2)
*/
void PWM_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
		
	//PWM输出通道引脚设置 PA6--左电机PWM   PA7--右电机PWM
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//计数器设置
	TIM_TimeBaseInitStructure.TIM_Period = 1000-1;  /*1000 占空比100%*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  //时钟预分频 不分频 时钟为72MHz
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  /* 时钟分频系数设置  不分频*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//PWM通用配置 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //输出比较极性高T
	
	//通道1设置
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);  //使能通道1
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//通道2设置
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//使能定时器4
	TIM_Cmd(TIM3,ENABLE); 
}

/*speed<=100*/
//左轮PWM输出
void Left_PWM(int speed)
{
	TIM_SetCompare1(TIM3,speed);
}
//右轮PWM输出
void Right_PWM(int speed)
{
	TIM_SetCompare2(TIM3,speed);
}
void Left_mode_Ahead(void)
{
	 Left_Mode1_H;
	 Left_Mode2_L;
}
void Left_mode_Back(void)
{
   Left_Mode1_L;
	 Left_Mode2_H;
}
void Left_mode_stop(void)
{
 Left_Mode1_L;
 Left_Mode2_L;
}
void Right_mode_Ahead(void)
{
	 Right_Mode1_H;
	 Right_Mode2_L;
}
void Right_mode_Back(void)
{
   Right_Mode1_L;
	 Right_Mode2_H;
}
void Right_mode_stop(void)
{
 Right_Mode1_L;
 Right_Mode2_L;
}
