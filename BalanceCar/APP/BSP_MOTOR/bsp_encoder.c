#include "bsp_encoder.h"
/*
  @���ܣ�����������
	@�ܽ�  ���� PA0 PA1
	       �ҵ�� PB6 PB7
*/
void Pwm_Catch_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	/*����ӿ�����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��PA�˿�ʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��PB�˿�ʱ��	
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//��������
	
	/*��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//�˿�����
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//�����趨������ʼ��GPIOA
	
	/*��*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//�˿�����
	GPIO_Init(GPIOB, &GPIO_InitStructure);         
	/* ������������ģʽ�Ĳ���ͨ��*/
	/* ���û�����ʱ��TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//ʹ�ܶ�ʱ��2��ʱ��  36MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 						//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period =0xFFFF; 						//�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//TIM���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//����TIM2�ı������   TIMx��x=2?3?4��    ����ģʽ3                 TI1����                                TI2����               
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//ʹ�ñ�����ģʽ3
	
	TIM_ICStructInit(&TIM_ICInitStructure); 
	TIM_ICInitStructure.TIM_ICFilter = 10;    //ѡ������Ƚ��˲���  ���õ����źŵĲ���Ƶ��
	TIM_ICInit(TIM2, &TIM_ICInitStructure); //��ʼ������

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);


	/* ������������ģʽ�Ļ�����ʱ��TIM4 */	
	/* ���û�����ʱ��TIM4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 						//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period =0xFFFF; 						//�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//TIM���ϼ���  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	//Reset counter
	TIM_SetCounter(TIM2,0);       //��TIMx�������Ĵ���ֵ��0
	TIM_Cmd(TIM2, ENABLE);     
	
	//Reset counter
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4, ENABLE); 
}

/*���ؾ����ϴζ�ȡʱ��εĵ�ƽ����������ô˺��������ڹ̶�*/
s32 Get_Right_Speed(void)	//Tim4
{
	s32 Encoder_TIM;
	Encoder_TIM = -(short)(TIM4 -> CNT);	//ȡ��ƽ��
	TIM4 -> CNT=0;							//�ֶ�����
	return Encoder_TIM;
}

/*���ؾ����ϴζ�ȡʱ��εĵ�ƽ����������ô˺��������ڹ̶�*/
s32 Get_Left_Speed(void)	//Tim2
{
	s32 Encoder_TIM;
	Encoder_TIM = -(short)(TIM2 -> CNT);	//ȡ��ƽ��
	TIM2 -> CNT=0;							//�ֶ�����
	return Encoder_TIM;
}
void Get_Speed(float * Speed_Left_CM_S,float * Speed_Right_CM_S,u32 T)
{
	s32 Lnumber,Rnumber;
	
	Lnumber = Get_Left_Speed();		//��ȡ������
	Rnumber = -Get_Right_Speed();	//��ȡ������
	
	*Speed_Left_CM_S  = (float)Lnumber / (float)T * 52.3598775f;		// (6.5*3.14159265 / 390) / ( T / 1000 ) = 52.3598775
	*Speed_Right_CM_S = (float)Rnumber / (float)T * 52.3598775f;
}
