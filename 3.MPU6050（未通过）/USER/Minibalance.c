#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
u8 Way_Angle=3;    
float Angle_Balance; 
int main(void)
{ 
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ��
	uart_init(72,9600);           //��ʼ������1
	IIC_Init();                     //ģ��IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��	
	DMP_Init();                     //��ʼ��DMP     
  Timer1_Init(49,7199);           //=====5MS��һ���жϷ�����
	while(1)
		{
				printf("�� �� �� �� �� �� Pitch:  %f\r\n  ",Angle_Balance);  //y 
		
		} 
}
