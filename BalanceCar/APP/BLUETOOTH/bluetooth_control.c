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
static int State_Flag;   //С��״̬��־λ 
u8 Receive_Data[80] = {0};   //���ݽ��ջ�����
u8 Data_to_String[80] = {0};  //
char returntemp[] = "$0,0,0,0,0,0,0,0,0,0,0,0cm,8.2V#";
void Bluetooth_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	//���崮�ڳ�ʼ���ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	/* config USART2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		/* config GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO	, ENABLE);
	/* Configure USART2 Tx  as alternate function push-pull �������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    
	/* Configure USART2 Rx  as input floating ��������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	
	
	
	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = 9600;//������9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����RTSCTSӲ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//ʹ�ܷ��ͽ���
	USART_Init(USART2, &USART_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	
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

	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//ע�⣡����ʹ��if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)���ж�  
    {  
		USART_ClearFlag(USART2, USART_FLAG_ORE); //��SR��ʵ���������־
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



void USART2_Send_Byte(unsigned char byte)   //���ڷ���һ���ֽ�
{
        USART_SendData(USART2, byte);        //ͨ���⺯��  ��������
        while( USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);  
        //�ȴ�������ɡ�   ��� USART_FLAG_TC �Ƿ���1�� 
        
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
	memcpy(Data_to_String, Receive_Data, num+1);     //��Receive_Dataָ��ָ��ģ�num+1�������ݷŵ�Data_To_Stringָ����
	memset(Receive_Data, 0x00, sizeof(Receive_Data));    //��Receive_Dataָ��ָ�������ȫ������Ϊ��0x00Ϊ��ʼλ��Ascllֵ
}
void Protocol(void)
{
	//USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//���ܽ����ж�
	//�ж����ݰ���Ч��
	switch (Data_to_String[1])
	{
		case '1':	 State_Flag = 1; USART2_Send_Char(returntemp);break;
		case '2':  State_Flag = 2; USART2_Send_Char(returntemp);break;
		case '3':  State_Flag = 3; USART2_Send_Char(returntemp);break;
		case '4':  State_Flag =  4; USART2_Send_Char(returntemp);break;
		case '0':  State_Flag = 0; USART2_Send_Char(returntemp);break;
		default: break;//State_Flag = 0; break;
		
	}

	/*��ֹ���ݶ���*/
	if(strlen((const char *)Data_to_String)<21)
	{
		Received_Finish_Flag = 0;  
		memset(Data_to_String, 0x00, sizeof(Data_to_String));  
		//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
		USART2_Send_Char("$ReceivePackError#"); //����Э�����ݰ� 
		return;
	}

	if (Data_to_String[3] == '1') //��ҡ
	{
		State_Flag = 5;
		USART2_Send_Char(returntemp); //����Э�����ݰ�  	
		
	}
	if (Data_to_String[3] == '2') //��ҡ
	{
		State_Flag = 6;
		USART2_Send_Char(returntemp); //����Э�����ݰ�  	
	}

	
	//��ѯPID
	if(Data_to_String[5]=='1')
	{
//		ProtocolGetPID();
	}
	else if(Data_to_String[5]=='2')  //�ָ�Ĭ��PID
	{
//		ResetPID();
		USART2_Send_Char("$OK#"); //����Э�����ݰ�  	
	}

	//�Զ��ϱ�
	if(Data_to_String[7]=='1')
	{
		g_autoup = 1;    
      	USART2_Send_Char("$OK#"); //����Э�����ݰ�  	
	}
	else if(Data_to_String[7]=='2')
	{		
		g_autoup = 0;		
		USART2_Send_Char("$OK#"); //����Э�����ݰ�  	
	}
	
	if (Data_to_String[9] == '1') //�ǶȻ����� $0,0,0,0,1,1,AP23.54,AD85.45,VP10.78,VI0.26#
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
		
//		Angle_pid.Kp = atof(apvalue);   //�Ƕ�PID��P����  ��ʱ���ò���
		
		
		memset(apad, 0x00, sizeof(apad));
		memcpy(apad, Data_to_String + pos + z + 1, int9num - (pos + z)); //�洢AD���������
		z = StringFind(apad, ",");
		if(z == -1) return;
		memcpy(advalue,apad+2, z-2);
		
//		Angle_pid.Kd=atof(advalue);    //�Ƕ�PID��΢�ֲ���

		USART2_Send_Char("$OK#"); //����Э�����ݰ�  				
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
		
//		Speed_pid.Kp = atof(vpvalue);  //�����ٶ�PID��P����
		
		
		memset(vpvi, 0x00, sizeof(vpvi));
		memcpy(vpvi, Data_to_String + pos + z + 1, int9num - (pos + z)); //�洢AD���������
		z = StringFind(vpvi, "#");
		if(z == -1) return;
		memcpy(vivalue,vpvi+2, z-2);
		
//		Speed_pid.Ki=atof(vivalue);  //�����ٶ�PID�Ļ��ֲ���

		USART2_Send_Char("$OK#"); //����Э�����ݰ�  				
	}
	
	Received_Finish_Flag = 0;  
	memset(Data_to_String, 0x00, sizeof(Data_to_String));  
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
}
void CarStateOut(u8 T)
{
	switch (State_Flag)
	{
		case 0: //ֹͣ
		{
      printf("STOP\r\n");
			Left_mode_stop();
			Right_mode_stop();

		} break; 					   

		case 1: //��ǰ�ٶ� 250  
		{
			printf("Go Ahead\r\n");
      Left_mode_Ahead();
			Left_PWM(500);
			Right_mode_Ahead();
			Right_PWM(300);
		  Get_Speed(&Speed_Left_CM_S,&Speed_Right_CM_S,T);
      printf("Speed_Left=%.2f  Speed_Right=%.2f\r\n",Speed_Left_CM_S,Speed_Right_CM_S);

		}break;	   
	
		case 2: //�����ٶ� -250
		{
			printf("Back\r\n");
			Left_mode_Back();
			Left_PWM(500);
      Right_mode_Back();
			Right_PWM(300);
			Get_Speed(&Speed_Left_CM_S,&Speed_Right_CM_S,T);
      printf("Speed_Left=%.2f  Speed_Right=%.2f\r\n",Speed_Left_CM_S,Speed_Right_CM_S);
			
		}break;
		case 3://��ת 
		{
       printf("Turn Left\r\n");
//			BST_fBluetoothDirectionNew= -300; 
//			chaoflag=1;

		}break;   
		
		case 4: //��ת
		{
        printf("Turn Right");
//			BST_fBluetoothDirectionNew= 300; 
//			chaoflag=1;

		}break;	
			
		case 5: //����
		{
			  printf("Left\r\n");
//			BST_fBluetoothDirectionNew = -driectionxco; 
//			chaoflag=1; 

		}break;
		case 6: //����
		{
			printf("Right\r\n");
//			BST_fBluetoothDirectionNew = driectionxco; 
//			chaoflag=1;
		}break;
		
		default:
//			BST_fBluetoothSpeed = 0;
//		   printf("stop\r\n");
 		break; 					   //ֹͣ
	}
}


