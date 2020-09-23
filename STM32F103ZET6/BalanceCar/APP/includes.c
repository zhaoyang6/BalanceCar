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

  Loop_Init();           //任务标志位初始化
	USART1_Init(115200);   //串口数据回传
	Bluetooth_Init();      //蓝牙初始化  使用USART3
	PWM_Init();            //电机控制PWM初始化
	Motor_Drive_Init();    //电机驱动板初始化
	Pwm_Catch_Init();      //编码器初始化
	IIC_Init();            //MPU6050IIC通信初始化
	MPU6050_initialize();
	DMP_Init();
	SysTick_Init();        //SysTick中断   1ms
//	Timer_Init(999,71);    //1ms中断，用于测量程序运行时间
}
//限幅函数
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
