#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
//u8 Way_Angle=3;    
//float Angle_Balance; 
int main()
{
	Stm32_Clock_Init(9);            //ϵͳʱ������
	Delay_Init(72);
	USART1_Init();
	IIC_Init();                     //ģ��IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��	
	DMP_Init();                     //��ʼ��DMP     
  Timer1_Init(49,7199);           //=====5MS��һ���жϷ�����
  while(1)
	{
	  printf("�� �� �� �� �� �� Pitch:  %.2f\r\n  ",Angle_Balance);  //y 
	}
}


