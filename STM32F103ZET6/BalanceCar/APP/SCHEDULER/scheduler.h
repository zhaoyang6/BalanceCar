#ifndef __SCHEDULER_H
#define	__SCHEDULER_H
#include "stm32f10x.h"
//�̱߳�־
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
void Loop_Init(void); //��ʼ���̱߳�־
void Loop_check(void); //������
void Duty_Loop(void);  //�����̷߳���
#endif
