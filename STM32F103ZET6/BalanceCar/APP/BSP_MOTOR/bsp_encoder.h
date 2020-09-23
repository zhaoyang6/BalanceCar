#ifndef _BSP_ENCODER_H
#define _BSP_ENCODER_H
#include "stm32f10x.h"
void Pwm_Catch_Init(void);  
s32 Get_Right_Speed(void);
s32 Get_Left_Speed(void);
void Get_Speed(float * Speed_Left_CM_S,float * Speed_Right_CM_S,u32 T);
#endif
