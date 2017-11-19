#include "public.h"	  //公共函数头文件
#include "bluetooth_control.h"
#include "printf.h"

int main()
{	
	Bluetooth_Init();
	uart_init(115200);
	printf("蓝牙数据测试(只有接收)\r\n");
	while(1)
	{
	 if (Received_Finish_Flag)
	   	{
			Data_To_String();
			Protocol();
		}
		/*通过状态控制小车*/
		CarStateOut();

//		printf("Ap:%.2f AD:%.2f SP:%.2f SI:%.2f\n",Angle_pid.Kp,Angle_pid.Kd,Speed_pid.Kp,Speed_pid.Ki);
	}
	
}



