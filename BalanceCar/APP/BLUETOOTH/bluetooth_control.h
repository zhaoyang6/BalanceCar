#ifndef _BLUETOOTH_CONTROL_H
#define _BLUETOOTH_CONTROL_H
#include "stm32f10x.h"
void SendAutoUp(void);
void Bluetooth_Init(void);
void Protocol(void);
void CarStateOut(u8 T);
void Data_To_String(void);
extern void Data_To_String(void); //���ƴ�������
extern u8 Received_Finish_Flag;   //�������ݰ�������ɱ�־

#endif
