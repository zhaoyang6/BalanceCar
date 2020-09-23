#include "bluetooth_control.h"
#include "bsp_usart1.h"
#include "math.h" 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsp_motor.h"
#include "bsp_encoder.h"
#include "includes.h"
float Speed_Left_CM_S=0.0f;
float Speed_Right_CM_S=0.0f;
int num = 0;
u8 Start_Flag = 0;
int int9num =0;
int g_autoup = 0;
u8 Received_Finish_Flag = 0;
static int State_Flag;   //小车状态标志位 
u8 Receive_Data[80] = {0};   //数据接收缓存区
u8 Data_to_String[80] = {0};  //
char returntemp[] = "$0,0,0,0,0,0,0,0,0,0,0,0cm,8.2V#";
void Bluetooth_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//定义串口初始化结构体
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		/* config GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO	, ENABLE);
	/* Configure USART2 Tx  as alternate function push-pull 推拉输出模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART2 Rx  as input floating 浮点输入模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	
	
	
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = 9600;//波特率9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8位数据
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//禁用RTSCTS硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//使能发送接收
	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断
	
	USART_Cmd(USART2, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}
void USART2_IRQHandler(void)
{  
	u8 uartvalue = 0;

	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断  
    {  
		USART_ClearFlag(USART2, USART_FLAG_ORE); //读SR其实就是清除标志
       	USART_ReceiveData(USART2);  		
    }
		
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)!=RESET)
	{
    	USART_ClearITPendingBit(USART2, USART_IT_RXNE);

		uartvalue = USART2->DR;
	    if(uartvalue == '$')
	    {
	      	Start_Flag = 1;
		    num = 0;
	    }
	    if(Start_Flag == 1)
	    {
	       	Receive_Data[num] = uartvalue;     
	    }  
	    if (Start_Flag == 1 && uartvalue == '#') 
	    {	    	
			Received_Finish_Flag = 1; 
			Start_Flag = 0;
			int9num = num;	
		
	    }
		num++;
		if(num >= 80)
		{
			num = 0;
			Start_Flag = 0;
			Received_Finish_Flag	= 0;
		}	 	
	}
}	 



void USART2_Send_Byte(unsigned char byte)   //串口发送一个字节
{
        USART_SendData(USART2, byte);        //通过库函数  发送数据
        while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  
        //等待发送完成。   检测 USART_FLAG_TC 是否置1； 
        
}
void USART2_Send_Char(char *s)
{
	char *p;
	p=s;
	while(*p != '\0')
	{
		USART2_Send_Byte(*p);
		p++;
	}	
}
int StringFind(const char *pSrc, const char *pDst)  
{  
    int i, j;  
    for (i=0; pSrc[i]!='\0'; i++)  
    {  
        if(pSrc[i]!=pDst[0])  
            continue;         
        j = 0;  
        while(pDst[j]!='\0' && pSrc[i+j]!='\0')  
        {  
            j++;  
            if(pDst[j]!=pSrc[i+j])  
            break;  
        }  
        if(pDst[j]=='\0')  
            return i;  
    }  
    return -1;  
}  



void Data_To_String(void)
{
	memcpy(Data_to_String, Receive_Data, num+1);     //将Receive_Data指针指向的（num+1）个数据放到Data_To_String指针中
	memset(Receive_Data, 0x00, sizeof(Receive_Data));    //将Receive_Data指针指向的数据全部设置为以0x00为起始位的Ascll值
}
void Protocol(void)
{
	//USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//禁能接收中断
	//判断数据包有效性
	switch (Data_to_String[1])
	{
		case '1':	 State_Flag = 1; USART2_Send_Char(returntemp);break;
		case '2':  State_Flag = 2; USART2_Send_Char(returntemp);break;
		case '3':  State_Flag = 3; USART2_Send_Char(returntemp);break;
		case '4':  State_Flag =  4; USART2_Send_Char(returntemp);break;
		case '0':  State_Flag = 0; USART2_Send_Char(returntemp);break;
		default: break;//State_Flag = 0; break;
		
	}

	/*防止数据丢包*/
	if(strlen((const char *)Data_to_String)<21)
	{
		Received_Finish_Flag = 0;  
		memset(Data_to_String, 0x00, sizeof(Data_to_String));  
		//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断
		USART2_Send_Char("$ReceivePackError#"); //返回协议数据包 
		return;
	}

	if (Data_to_String[3] == '1') //左摇
	{
		State_Flag = 5;
		USART2_Send_Char(returntemp); //返回协议数据包  	
		
	}
	if (Data_to_String[3] == '2') //右摇
	{
		State_Flag = 6;
		USART2_Send_Char(returntemp); //返回协议数据包  	
	}

	
	//查询PID
	if(Data_to_String[5]=='1')
	{
//		ProtocolGetPID();
	}
	else if(Data_to_String[5]=='2')  //恢复默认PID
	{
//		ResetPID();
		USART2_Send_Char("$OK#"); //返回协议数据包  	
	}

	//自动上报
	if(Data_to_String[7]=='1')
	{
		g_autoup = 1;    
      	USART2_Send_Char("$OK#"); //返回协议数据包  	
	}
	else if(Data_to_String[7]=='2')
	{		
		g_autoup = 0;		
		USART2_Send_Char("$OK#"); //返回协议数据包  	
	}
	
	if (Data_to_String[9] == '1') //角度环更新 $0,0,0,0,1,1,AP23.54,AD85.45,VP10.78,VI0.26#
	{
		//$0,0,0,0,1,1,AP23.54,AD85.45,VP10.78,VI0.26#

		int pos,z; 
		char apad[20] = {0},apvalue[8] = {0},advalue[8] = {0};			
		pos = StringFind((const char *)Data_to_String, (const char *)"AP");
		if(pos == -1) return;
		
		memcpy(apad,Data_to_String+pos,int9num-pos);

		//AP23.54,AD85.45,VP10.78,VI0.26#
		z = StringFind(apad, ",");
		if(z == -1) return;
		memcpy(apvalue, apad+2, z-2);
		
//		Angle_pid.Kp = atof(apvalue);   //角度PID的P参数  暂时还用不到
		
		
		memset(apad, 0x00, sizeof(apad));
		memcpy(apad, Data_to_String + pos + z + 1, int9num - (pos + z)); //存储AD后面的数据
		z = StringFind(apad, ",");
		if(z == -1) return;
		memcpy(advalue,apad+2, z-2);
		
//		Angle_pid.Kd=atof(advalue);    //角度PID的微分参数

		USART2_Send_Char("$OK#"); //返回协议数据包  				
	}
		
  	if(Data_to_String[11] == '1')
	{
		int pos,z; 
		char vpvi[20] = {0},vpvalue[8] = {0},vivalue[8] = {0};
			
		pos = StringFind((const char *)Data_to_String, (const char *)"VP");
		if(pos == -1) return;
		
		memcpy(vpvi, Data_to_String+pos, int9num-pos);
		//y=strchr(apad,'AP');
		//AP23.54,AD85.45,VP10.78,VI0.26#
		z = StringFind(vpvi, ",");
		if(z == -1) return;
		memcpy(vpvalue, vpvi+2, z-2);
		
//		Speed_pid.Kp = atof(vpvalue);  //关于速度PID的P参数
		
		
		memset(vpvi, 0x00, sizeof(vpvi));
		memcpy(vpvi, Data_to_String + pos + z + 1, int9num - (pos + z)); //存储AD后面的数据
		z = StringFind(vpvi, "#");
		if(z == -1) return;
		memcpy(vivalue,vpvi+2, z-2);
		
//		Speed_pid.Ki=atof(vivalue);  //关于速度PID的积分参数

		USART2_Send_Char("$OK#"); //返回协议数据包  				
	}
	
	Received_Finish_Flag = 0;  
	memset(Data_to_String, 0x00, sizeof(Data_to_String));  
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能接收中断
}
void CarStateOut(u8 T)
{
	switch (State_Flag)
	{
		case 0: //停止
		{
      printf("STOP\r\n");
			Left_mode_stop();
			Right_mode_stop();

		} break; 					   

		case 1: //向前速度 250  
		{
			printf("Go Ahead\r\n");
      Left_mode_Ahead();
			Left_PWM(500);
			Right_mode_Ahead();
			Right_PWM(300);
		  Get_Speed(&Speed_Left_CM_S,&Speed_Right_CM_S,T);
      printf("Speed_Left=%.2f  Speed_Right=%.2f\r\n",Speed_Left_CM_S,Speed_Right_CM_S);

		}break;	   
	
		case 2: //后退速度 -250
		{
			printf("Back\r\n");
			Left_mode_Back();
			Left_PWM(500);
      Right_mode_Back();
			Right_PWM(300);
			Get_Speed(&Speed_Left_CM_S,&Speed_Right_CM_S,T);
      printf("Speed_Left=%.2f  Speed_Right=%.2f\r\n",Speed_Left_CM_S,Speed_Right_CM_S);
			
		}break;
		case 3://左转 
		{
       printf("Turn Left\r\n");
//			BST_fBluetoothDirectionNew= -300; 
//			chaoflag=1;

		}break;   
		
		case 4: //右转
		{
        printf("Turn Right");
//			BST_fBluetoothDirectionNew= 300; 
//			chaoflag=1;

		}break;	
			
		case 5: //左旋
		{
			  printf("Left\r\n");
//			BST_fBluetoothDirectionNew = -driectionxco; 
//			chaoflag=1; 

		}break;
		case 6: //右旋
		{
			printf("Right\r\n");
//			BST_fBluetoothDirectionNew = driectionxco; 
//			chaoflag=1;
		}break;
		
		default:
//			BST_fBluetoothSpeed = 0;
//		   printf("stop\r\n");
 		break; 					   //停止
	}
}


