#ifndef __SCHEDULER_H
#define	__SCHEDULER_H
#include "stm32f10x.h"
//线程标志
typedef struct
{
	 u8 Check_Flag;
   u8 Flag_1ms;
   u8 Flag_2ms;
   u8 Flag_5ms;
	 u8 Flag_10ms;
   u8 Flag_20ms;
   u8 Flag_50ms;
	 u8 Error_Flag;

}loop_t;
void Loop_Init(void); //初始化线程标志
void Loop_check(void); //错误检查
void Duty_Loop(void);  //任务线程分配
#endif
