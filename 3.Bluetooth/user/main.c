#include "public.h"	  //��������ͷ�ļ�
#include "bluetooth_control.h"
#include "printf.h"

int main()
{	
	Bluetooth_Init();
	uart_init(115200);
	printf("�������ݲ���(ֻ�н���)\r\n");
	while(1)
	{
	 if (Received_Finish_Flag)
	   	{
			Data_To_String();
			Protocol();
		}
		/*ͨ��״̬����С��*/
		CarStateOut();

//		printf("Ap:%.2f AD:%.2f SP:%.2f SI:%.2f\n",Angle_pid.Kp,Angle_pid.Kd,Speed_pid.Kp,Speed_pid.Ki);
	}
	
}



