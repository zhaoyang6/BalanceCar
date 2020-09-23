#ifndef _PID_H
#define _PID_H
#include "stm32f10x.h"
typedef struct 
{
  u32 Kp;
	u32 Ki;
	u32 Kd;
  u32 Last_Data; //�ϴβ�����
	u32 Kd_Error; //΢�ֲ�(��ǰ�����������ϴβ�������֮��)
	u32 Ki_I;     //���ֺ� ��ǰ�����������ϴβ�������֮��
	u32 Out;      //���ݵ����
}PID;
void Angle_Balance(float pitch, float Expect_Pitch);
void Speed_Balance(u32 Expect_Speed,u32 Measure_Speed);
#endif
