/*
  @此文件用于存放所有的全局变量和结构体以及所有头文件
*/

#ifndef _INCLUDES_H
#define _INCLUDES_H
#include "stm32f10x.h"
#include "pid.h"
#include "scheduler.h"
u32 LIMIT(u32 yournumber,u32 Upper_Limit,u32 Lower_Limit);//限幅函数
extern PID Speed_Pid;  //速度PID
extern PID Angle_Pid;  //角度PID
extern loop_t loop;
#endif
