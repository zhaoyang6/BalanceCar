#ifndef _PID_H
#define _PID_H
#include "stm32f10x.h"
typedef struct 
{
  u32 Kp;
	u32 Ki;
	u32 Kd;
  u32 Last_Data; //上次测量量
	u32 Kd_Error; //微分差(当前测量数据与上次测量数据之差)
	u32 Ki_I;     //积分和 当前测量数据与上次测量数据之和
	u32 Out;      //数据的输出
}PID;
void Angle_Balance(float pitch, float Expect_Pitch);
void Speed_Balance(u32 Expect_Speed,u32 Measure_Speed);
#endif
