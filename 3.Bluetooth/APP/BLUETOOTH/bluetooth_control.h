#ifndef _BLUETOOTH_CONTROL_H
#define _BLUETOOTH_CONTROL_H
#include "stm32f10x.h"
extern u8 Received_Finish_Flag;
void SendAutoUp(void);
void Bluetooth_Init(void);
void Protocol(void);
void CarStateOut(void);
void Data_To_String(void);
extern void Data_To_String(void); //复制串口数据
#endif
