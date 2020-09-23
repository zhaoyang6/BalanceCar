#include "pid.h"
PID Speed_Pid; //速度PID
PID Angle_Pid; //角度PID 
void Pid_Init(void)
{
 Angle_Pid.Kp=100;
 Angle_Pid.Ki=0;
 Angle_Pid.Kd=10;
 Angle_Pid.Last_Data=0;
 Speed_Pid.Kp=100;
 Speed_Pid.Ki=10;
 Speed_Pid.Kd=0;
 Speed_Pid.Last_Data=0;
}
/*
  @功能：输出速度控制的PWM
	@公式：a=Angle_Pid.Kp*Pitch+Angle_Pid.Kd*(Pitch-Angle_Pid.Last_Data)
	@公式参数解释 a：电机的加速度  Pitch：车的姿态（倾斜角度） 
	@电机的加速度与电机的PWM之间有一定的线性关系，故而我们可以通过调节PID参数来使其在数值上相等
	 具体的电机加速度与PWM的关系可由电机拖动课程中所学知识求得
*/
float Start_Angle=0;  //此变量的值与小车的初始状态有关
void Angle_Balance(float pitch, float Expect_Pitch)
{
	u32 Angle;
	u32 Error; //反馈后的差
	Angle = (u32)(pitch-Start_Angle);  ///真实偏移值
	Error=Expect_Pitch-Angle;
	Angle_Pid.Kd_Error+=Error-Angle_Pid.Last_Data; //微分差
	Angle_Pid.Out=Angle_Pid.Kp*Angle+Angle_Pid.Kd*Angle_Pid.Kd_Error;
	Angle_Pid.Last_Data=Error;	
}
/*
  @功能：得到速度控制的PWM
  @输入参数：期望速度（角度环的输出）, 测量出的速度（由减速器测得）
  @公式：PWM=Kp*Error +Ki*Error;
*/
u32 Ki_Sum=0;  //积分累加和
void Speed_Balance(u32 Expect_Speed,u32 Measure_Speed)
{
  u32 Error;
	Error=Expect_Speed-Measure_Speed;  //速度反馈
	Ki_Sum+=Speed_Pid.Ki*Error;        //积分和
	Speed_Pid.Out=Speed_Pid.Kp*Error+Ki_Sum; //输出
}

