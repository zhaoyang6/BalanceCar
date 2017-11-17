#include "motor.h"
#include "encoder.h"
#include "variate.h"  //所有的全局变量都放在这里
#include "printf.h"  
#include "timer.h"
int main()
{
	float Speed_Left_CM_S=0.0f;
	float Speed_Right_CM_S=0.0f;
	u32 T=2;  //随意写的数据，此数据应该和调用线程的时间有关
	Motor_Drive_Init();
  PWM_Init();
	Pwm_Catch_Init();
	printf_init();
//	Left_mode_Ahead();
//	Right_mode_Back();

	while(1)
	{
		Left_mode_Ahead();
	  Right_mode_Back();
		Left_PWM(500);
		Right_PWM(500);
		Get_Speed(&Speed_Left_CM_S,&Speed_Right_CM_S,T);
    printf("Speed_Left=%.2f  Speed_Right=%.2f\r\n",Speed_Left_CM_S,Speed_Right_CM_S);

		
	}	
}



