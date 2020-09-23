#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f10x.h"
void delay_us(u32 us);
void delay_ms(u32 ms);
void TIM3_init(void);
void Time_Start(void);
u32 Time_End(void);
#endif
