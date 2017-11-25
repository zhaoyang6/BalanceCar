#include "bsp_motor.h"
/*
@���ܣ�����������ʼ��
@�ܽţ�ת����ƣ�����PC4 PC5  �ҵ�� PC6 PC7
       ʹ�ܿ��� PC8
*/
void Motor_Drive_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
		
	GPIO_SetBits(GPIOC,GPIO_Pin_8);  //������ʹ��
	
}
/*
 @���ܣ�PWM�����ʼ��
 @�ܽţ�PA6(TIM3_CH1) PA7(TIM3_CH2)
*/
void PWM_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
		
	//PWM���ͨ���������� PA6--����PWM   PA7--�ҵ��PWM
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//����������
	TIM_TimeBaseInitStructure.TIM_Period = 1000-1;  /*1000 ռ�ձ�100%*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  //ʱ��Ԥ��Ƶ ����Ƶ ʱ��Ϊ72MHz
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  /* ʱ�ӷ�Ƶϵ������  ����Ƶ*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	//PWMͨ������ 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //����Ƚϼ��Ը�T
	
	//ͨ��1����
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);  //ʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//ͨ��2����
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//ʹ�ܶ�ʱ��4
	TIM_Cmd(TIM3,ENABLE); 
}

/*speed<=100*/
//����PWM���
void Left_PWM(int speed)
{
	TIM_SetCompare1(TIM3,speed);
}
//����PWM���
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
