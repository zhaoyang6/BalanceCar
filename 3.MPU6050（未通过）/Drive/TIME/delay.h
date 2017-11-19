#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f10x.h"
void Delay_Init(u8 SYSCLK);
void delay_us(u32 us);
void delay_ms(u16 ms);
#endif
