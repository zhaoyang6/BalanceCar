#include "bsp_encoder.h"
/*
  @功能：编码器捕获
	@管脚  左电机 PA0 PA1
	       右电机 PB6 PB7
*/
void Pwm_Catch_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	/*输入接口配置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能PA端口时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能PB端口时钟	
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//浮空输入
	
	/*左*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	//端口配置
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//根据设定参数初始化GPIOA
	
	/*右*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口配置
	GPIO_Init(GPIOB, &GPIO_InitStructure);         
	/* 配置左轮输入模式的捕获通道*/
	/* 配置基本定时器TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			//使能定时器2的时钟  36MHz
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 						//预分频器 
	TIM_TimeBaseStructure.TIM_Period =0xFFFF; 						//设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//TIM向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	//设置TIM2的编码界面   TIMx（x=2?3?4）    编码模式3                 TI1极性                                TI2极性               
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//使用编码器模式3
	
	TIM_ICStructInit(&TIM_ICInitStructure); 
	TIM_ICInitStructure.TIM_ICFilter = 10;    //选择输入比较滤波器  设置的是信号的采样频率
	TIM_ICInit(TIM2, &TIM_ICInitStructure); //初始化外设

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);


	/* 配置右轮输入模式的基本定时器TIM4 */	
	/* 配置基本定时器TIM4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; 						//预分频器 
	TIM_TimeBaseStructure.TIM_Period =0xFFFF; 						//设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			//选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//TIM向上计数  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);	//使用编码器模式3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	//Reset counter
	TIM_SetCounter(TIM2,0);       //将TIMx计数器寄存器值置0
	TIM_Cmd(TIM2, ENABLE);     
	
	//Reset counter
	TIM_SetCounter(TIM4,0);
	TIM_Cmd(TIM4, ENABLE); 
}

/*返回距离上次读取时间段的电平数，建议调用此函数的周期固定*/
s32 Get_Right_Speed(void)	//Tim4
{
	s32 Encoder_TIM;
	Encoder_TIM = -(short)(TIM4 -> CNT);	//取电平数
	TIM4 -> CNT=0;							//手动清零
	return Encoder_TIM;
}

/*返回距离上次读取时间段的电平数，建议调用此函数的周期固定*/
s32 Get_Left_Speed(void)	//Tim2
{
	s32 Encoder_TIM;
	Encoder_TIM = -(short)(TIM2 -> CNT);	//取电平数
	TIM2 -> CNT=0;							//手动清零
	return Encoder_TIM;
}
void Get_Speed(float * Speed_Left_CM_S,float * Speed_Right_CM_S,u32 T)
{
	s32 Lnumber,Rnumber;
	
	Lnumber = Get_Left_Speed();		//读取编码器
	Rnumber = -Get_Right_Speed();	//读取编码器
	
	*Speed_Left_CM_S  = (float)Lnumber / (float)T * 52.3598775f;		// (6.5*3.14159265 / 390) / ( T / 1000 ) = 52.3598775
	*Speed_Right_CM_S = (float)Rnumber / (float)T * 52.3598775f;
}
