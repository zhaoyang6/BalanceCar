#include "includes.h"
#include "bluetooth_control.h"
#include "bsp_usart1.h"
#include "bsp_SysTick.h"
#include "bsp_motor.h"
#include "bsp_encoder.h"
#include "sys.h"
//#include "bsp_tim3.h"
void All_Init(void)
{

  Loop_Init();           //�����־λ��ʼ��
	USART1_Init(115200);   //�������ݻش�
	Bluetooth_Init();      //������ʼ��  ʹ��USART3
	PWM_Init();            //�������PWM��ʼ��
	Motor_Drive_Init();    //����������ʼ��
	Pwm_Catch_Init();      //��������ʼ��
	IIC_Init();            //MPU6050IICͨ�ų�ʼ��
	MPU6050_initialize();
	DMP_Init();
	SysTick_Init();        //SysTick�ж�   1ms
//	Timer_Init(999,71);    //1ms�жϣ����ڲ�����������ʱ��
}
//�޷�����
u32 LIMIT(u32 yournumber,u32 Upper_Limit,u32 Lower_Limit)
{
	if(yournumber>(Upper_Limit-10))
	{
		yournumber=Upper_Limit-10;
	}
	else if(yournumber<(Lower_Limit+10))
	{
	  yournumber=Lower_Limit+10;
	}
	else
	{
		yournumber=yournumber;
	}
	return yournumber;		
}
