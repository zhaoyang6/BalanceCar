#include "timer.h"
/*
1.��ʱ������
ʵ��delay_us��delay_ms
ʵ�ַ�ʽ��whileѭ��
�ӿڣ�delay_us��delay_ms�����յ������������������������������ת����ʹ�õ���ʱ������ȥ��

2.΢���ʱ��
���ڼ����������ʱ����
*/

//�ڲ���������
void Delay_Us(u32 myUs);
void Delay_Ms(u32 myMs);

//**************************************************************************
//                         ����ʱ����
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

//*************************************************************************************
//	΢���ʱ�������ڼ��������ü��
//*************************************************************************************
void TIM3_init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	/* ����TIM3ʱ������*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, DISABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	/*TIM3����ж�*/
	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	
	// ������ռ���ȼ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	// ���������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*��ʼ��ʱ*/
void Time_Start(void)
{
	TIM3 -> CNT = 0;
	TIM_Cmd(TIM3, ENABLE);
}

/*������ֵֹͣ��ʱ������ʱ��ֵ����λus*/
int ms;
u32 Time_End(void)
{
	int countertime;
	countertime=(TIM3 -> CNT)+(1000*ms);  
	TIM_Cmd(TIM3, DISABLE);
	ms=0;
	return countertime;
}
/*����жϷ�����*/
void TIM3_IRQHandler (void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
	ms++;
}
