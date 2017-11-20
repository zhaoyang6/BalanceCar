#include "sys.h"
int main(void)
{
	MY_NVIC_PriorityGroupConfig(0);
  Stm32_Clock_Init(9);
	delay_init(72);
	uart_init(72,9600);
	IIC_Init();
	MPU6050_initialize();
	DMP_Init();
	while(1)
	{
	  Read_DMP();
		printf("Yaw=%.2f Pitch=%.2f Roll=%.2f\r\n",Yaw,Pitch,Roll);
	}
}
