#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
//u8 Way_Angle=3;    
//float Angle_Balance; 
int main()
{
	Stm32_Clock_Init(9);            //系统时钟设置
	Delay_Init(72);
	USART1_Init();
	IIC_Init();                     //模拟IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化	
	DMP_Init();                     //初始化DMP     
  Timer1_Init(49,7199);           //=====5MS进一次中断服务函数
  while(1)
	{
	  printf("互 补 滤 波 输 出 Pitch:  %.2f\r\n  ",Angle_Balance);  //y 
	}
}


