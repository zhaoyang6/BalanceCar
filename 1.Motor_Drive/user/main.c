#include "motor.h"
#include "encoder.h"
#include "variate.h"  //���е�ȫ�ֱ�������������
#include "printf.h"  
#include "timer.h"
int main()
{
	float Speed_Left_CM_S=0.0f;
	float Speed_Right_CM_S=0.0f;
	u32 T=2;  //����д�����ݣ�������Ӧ�ú͵����̵߳�ʱ���й�
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



