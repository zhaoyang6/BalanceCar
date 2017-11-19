#include "pid.h"

//PID参数
void PID_parameter(void)
{
  Speed_pid.Kp=10;
	Speed_pid.Ki=10;
	Speed_pid.Kd=10;
	Speed_pid.Out=10;
	Angle_pid.Kp=10;
	Angle_pid.Ki=10;
	Angle_pid.Kd=10;
	Angle_pid.Out=1;
}

//平衡控制
//float E_I=0; // 积分
float System_Angle=0.0f;  //摆正小车时的角度，由于安装位置导致的偏差

int Balance_Control(float Pitch,short Gyor_y)
{
	float Angle_Error;
	Angle_Error=Pitch-System_Angle;   //角度偏差
//	E_I+=Angle_Error;
	Angle_pid.Out=Angle_pid.Kp*Angle_Error+ Angle_pid.Kd*Gyor_y;
	return ((int)Angle_pid.Out);
}

//速度控制
float L_E=0,  //积分值
	    R_E=0;  //积分值
void Speed_Control(int Encoder_L,int Encoder_R,int *Out_Left,int *Out_Right)
{
  float L_Error,R_Error;
	int Left_Out,Right_Out;
	L_E+=L_Error*Speed_pid.Ki;
	R_E+=R_Error*Speed_pid.Ki;
	Left_Out=(int)((Speed_pid.Kp*L_Error)+L_E);
	Right_Out=(int)((Speed_pid.Kp*R_Error)+R_E);
  *Out_Left=Left_Out;
	*Out_Right=Right_Out;
}


