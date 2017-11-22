#include "pid.h"
PID Speed_Pid; //�ٶ�PID
PID Angle_Pid; //�Ƕ�PID 
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
  @���ܣ�����ٶȿ��Ƶ�PWM
	@��ʽ��a=Angle_Pid.Kp*Pitch+Angle_Pid.Kd*(Pitch-Angle_Pid.Last_Data)
	@��ʽ�������� a������ļ��ٶ�  Pitch��������̬����б�Ƕȣ� 
	@����ļ��ٶ�������PWM֮����һ�������Թ�ϵ���ʶ����ǿ���ͨ������PID������ʹ������ֵ�����
	 ����ĵ�����ٶ���PWM�Ĺ�ϵ���ɵ���϶��γ�����ѧ֪ʶ���
*/
float Start_Angle=0;  //�˱�����ֵ��С���ĳ�ʼ״̬�й�
void Angle_Balance(float pitch, float Expect_Pitch)
{
	u32 Angle;
	u32 Error; //������Ĳ�
	Angle = (u32)(pitch-Start_Angle);  ///��ʵƫ��ֵ
	Error=Expect_Pitch-Angle;
	Angle_Pid.Kd_Error+=Error-Angle_Pid.Last_Data; //΢�ֲ�
	Angle_Pid.Out=Angle_Pid.Kp*Angle+Angle_Pid.Kd*Angle_Pid.Kd_Error;
	Angle_Pid.Last_Data=Error;	
}
/*
  @���ܣ��õ��ٶȿ��Ƶ�PWM
  @��������������ٶȣ��ǶȻ��������, ���������ٶȣ��ɼ�������ã�
  @��ʽ��PWM=Kp*Error +Ki*Error;
*/
u32 Ki_Sum=0;  //�����ۼӺ�
void Speed_Balance(u32 Expect_Speed,u32 Measure_Speed)
{
  u32 Error;
	Error=Expect_Speed-Measure_Speed;  //�ٶȷ���
	Ki_Sum+=Speed_Pid.Ki*Error;        //���ֺ�
	Speed_Pid.Out=Speed_Pid.Kp*Error+Ki_Sum; //���
}

