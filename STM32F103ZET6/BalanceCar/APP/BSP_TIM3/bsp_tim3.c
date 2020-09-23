#include "bsp_tim3.h"
#include "bsp_usart1.h"
void Timer_Init(u32 period,u32 prescaler)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
  NVIC_InitTypeDef NVIC_InitStrucuture;
	
	/* ����TIM3ʱ������,ÿ1ms�ж�һ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //ʹ��TIM3��ʱ��
	TIM_TimeBaseStructure.TIM_Period = period;             //��������  1000��Ϊһ����
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;           //Ԥ��Ƶϵ��  72MHz/72=1MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;          //ʱ�ӷָ� ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, DISABLE);                                //�˴�ʱ�Ӳ��򿪣��ڲ���ʱ����ȷ����ʱ��׼ȷ��
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  //�ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStrucuture.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStrucuture.NVIC_IRQChannelPreemptionPriority=2;//������ռʽ���ȼ�
	NVIC_InitStrucuture.NVIC_IRQChannelSubPriority=2;       //������Ӧʽ���ȼ�
	NVIC_InitStrucuture.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStrucuture);
}
int ms;
//TIM3�жϷ�����
void TIM3_IRQHandler (void)
{
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	
	ms++;
}
//��ʱ��ʼ����
void Time_Start(void)
{
	TIM3->CNT=0;    //ÿ�μ�����Ҫ�Ѽ����Ĵ������㣬��ȷ��ÿ�μ�����׼ȷ��
	TIM_Cmd(TIM3,ENABLE);//����Ҫ����ʱ�Ŵ�ʱ��
}
//��ʱ��������������ʱ�䣬��λΪus
void Time_End(void)
{
  int time=0;  //�˱���ֻ��Ϊ�˳��ؼ�������ʱ��
	time=(TIM3->CNT+1)+(1000*ms); //ʱ��ĵ�λΪus��֮���Բ��������λ�������С�����㣬������ٶ�
	TIM_Cmd(TIM3,DISABLE); //����ʱ�ӹر�
	ms=0;
	printf("T=%dus\r\n",time);  	
}
