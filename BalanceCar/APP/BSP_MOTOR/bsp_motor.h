#ifndef _BSP_MOTOR_H
#define _BSP_MOTOR_H
#include "stm32f10x.h"

//����ģʽ
#define Left_Mode1_H  GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define Left_Mode1_L  GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define Left_Mode2_H  GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define Left_Mode2_L  GPIO_ResetBits(GPIOC,GPIO_Pin_5)
//�ҵ��ģʽ
#define Right_Mode1_H  GPIO_SetBits(GPIOC,GPIO_Pin_6)
#define Right_Mode1_L  GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define Right_Mode2_H  GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define Right_Mode2_L  GPIO_ResetBits(GPIOC,GPIO_Pin_7)

void PWM_Init(void);             //PWM��ʼ��
void Motor_Drive_Init(void);     //����������ʼ��
void Left_PWM(int speed);        //����PWW����
void Right_PWM(int speed);       //�ҵ��PWM����
void Left_mode_Ahead(void);      //����ǰ��
void Left_mode_Back(void);       //��������
void Left_mode_stop(void);       //����ֹͣ
void Right_mode_Ahead(void);     //�ҵ��ǰ��
void Right_mode_Back(void);      //�ҵ����� 
void Right_mode_stop(void);      //�ҵ��ֹͣ
#endif
