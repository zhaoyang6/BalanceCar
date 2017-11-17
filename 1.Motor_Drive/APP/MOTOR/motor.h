#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"

//左电机模式
#define Left_Mode1_H  GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define Left_Mode1_L  GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define Left_Mode2_H  GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define Left_Mode2_L  GPIO_ResetBits(GPIOC,GPIO_Pin_5)
//右电机模式
#define Right_Mode1_H  GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define Right_Mode1_L  GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define Right_Mode2_H  GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define Right_Mode2_L  GPIO_ResetBits(GPIOC,GPIO_Pin_7)

void PWM_Init(void);
void Motor_Drive_Init(void);
void Left_PWM(int speed);
void Right_PWM(int speed);
void Left_mode_Ahead(void);
void Left_mode_Back(void);
void Left_mode_stop(void);
void Right_mode_Ahead(void);
void Right_mode_Back(void);
void Right_mode_stop(void);
#endif
