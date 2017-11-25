#ifndef _INCLUDES_H
#define _INCLUDES_H
#include "stm32f10x.h"
#include "pid.h"
#include "scheduler.h"
u32 LIMIT(u32 yournumber,u32 Upper_Limit,u32 Lower_Limit);//限幅函数
extern PID Speed_Pid;  //速度PID
extern PID Angle_Pid;  //角度PID
extern loop_t loop;    //线程标志结构体
extern float Speed_Left_CM_S;  //左轮速度
extern float Speed_Right_CM_S; //右轮速度

void All_Init(void);
#endif
