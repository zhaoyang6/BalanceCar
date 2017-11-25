#include "scheduler.h"
#include "bluetooth_control.h"
#include "bsp_usart1.h"
#include "sys.h"
//#include "bsp_tim3.h"
loop_t loop;  //�����־�ṹ��
//��������ʼ��---���б�־λ��0
void Loop_Init(void)
{
	loop.Check_Flag=0;
  loop.Flag_1ms=0;
	loop.Flag_2ms=0;
	loop.Flag_5ms=0;
	loop.Flag_10ms=0;
	loop.Flag_20ms=0;
  loop.Flag_50ms=0;
	loop.Error_Flag=0;
}

void Duty_1ms(void)
{
	u8 T=1;
}
void Duty_2ms(void)
{ 
	u8 T=2;
//	Time_Start();
//		if (Received_Finish_Flag)
//	   	{
//			Data_To_String();
//			Protocol();
//		}
//		/*ͨ��״̬����С��*/
//		CarStateOut(T);
//  Time_End();
}
void Duty_5ms(void)
{
	u8 T=5;
	  Read_DMP();
		printf("Yaw=%.2f Pitch=%.2f Roll=%.2f T=%d\r\n",Yaw,Pitch,Roll,T);
}
void Duty_10ms(void)
{ 
	u8 T=10;
	
}

void Duty_20ms(void)
{
	u8 T=20;
}
void Duty_50ms(void)
{ 
	u8 T=50;
	
}


void Duty_Loop(void)
{
	if(loop.Check_Flag == 1)
	{
		Duty_1ms();							//����1ms������
		
		if(loop.Flag_2ms >= 2)
		{
			loop.Flag_2ms = 0;
			Duty_2ms();						//����2ms������
		}
		if( loop.Flag_5ms >= 5 )
		{
			loop.Flag_5ms = 0;
			Duty_5ms();						//����5ms������
		}
		if( loop.Flag_10ms >= 10 )
		{
			loop.Flag_10ms = 0;
			Duty_10ms();					//����10ms������
		}
		if( loop.Flag_20ms >= 20 )
		{
			loop.Flag_20ms = 0;
			Duty_20ms();					//����20ms������
		}
		if( loop.Flag_50ms >= 50 )
		{
			loop.Flag_50ms = 0;
			Duty_50ms();					//����50ms������
		}
		
		loop.Check_Flag = 0;	//�����������
	}
}
//������
void Loop_check(void)
{
	loop.Flag_2ms++;
	loop.Flag_5ms++;
	loop.Flag_10ms++;
	loop.Flag_20ms++;
	loop.Flag_50ms++;
	
	if(loop.Check_Flag == 1)	//���������check_flag�����ﻹ��1��û�б���0��
								//֤����ѭ������1ms������û�������꣬������check_flagû�����е�
	{
		loop.Error_Flag++;		//ÿ�γ������⣬error_flag+1
	}
	
	loop.Check_Flag = 1;
}
