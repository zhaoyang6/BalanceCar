#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H
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

void PWM_Init(void);             //PWM初始化
void Motor_Drive_Init(void);     //电机驱动板初始化
void Left_PWM(int speed);        //左电机PWW设置
void Right_PWM(int speed);       //右电机PWM设置
void Left_mode_Ahead(void);      //左电机前进
void Left_mode_Back(void);       //左电机后退
void Left_mode_stop(void);       //左电机停止
void Right_mode_Ahead(void);     //右电机前进
void Right_mode_Back(void);      //右电机向后 
void Right_mode_stop(void);      //右电机停止
#endif
