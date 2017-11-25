#ifndef _INCLUDES_H
#define _INCLUDES_H
#include "stm32f10x.h"
#include "pid.h"
#include "scheduler.h"
u32 LIMIT(u32 yournumber,u32 Upper_Limit,u32 Lower_Limit);//�޷�����
extern PID Speed_Pid;  //�ٶ�PID
extern PID Angle_Pid;  //�Ƕ�PID
extern loop_t loop;    //�̱߳�־�ṹ��
extern float Speed_Left_CM_S;  //�����ٶ�
extern float Speed_Right_CM_S; //�����ٶ�

void All_Init(void);
#endif
