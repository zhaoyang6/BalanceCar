#ifndef _BSP_TIM3_H
#define _BSP_TIM3_H
#include "stm32f10x.h"
void Timer_Init(u32 period,u32 prescaler);
void Time_Start(void);
void Time_End(void);
#endif
