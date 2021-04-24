//USART1_TX   GPIOA.9
//USART1_RX	  GPIOA.10
#include "sys.h"
#include "usart.h"	
#include "string.h"	
#include "stdarg.h"	
#include "delay.h"	

////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
//		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
//} 
#endif	


//����2������
u8 USART2_RX_BUF[USART_REC_LEN] ;           
u8 USART2_TX_BUF[USART_REC_LEN] ;           

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	  
 

//******************************************************************************              
//name:             USART2_Init             
//introduce:        USART2��ʼ��        
//****************************************************************************** 
void uart2_init(u32 bound)//laser
{
		GPIO_InitTypeDef GPIO_InitStructure;   //����һ���ṹ�������������ʼ��GPIO
  	USART_InitTypeDef USART_InitStructure;   //���ڽṹ�嶨��
		NVIC_InitTypeDef NVIC_InitStructure;  //�жϽṹ�嶨��
 
  	//����GPIOA��USART2 ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  	
		//����GPIO��ģʽ��IO�� TX     
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          //�������PA2                                                                                          
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
  	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ����������
		//RX
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;          //��������PA3                                                                              
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//��������
  	GPIO_Init(GPIOA,&GPIO_InitStructure);       			 //��ʼ���������
			
		//NVIC ����
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             //�����ж����ȼ�����
  	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //��USART2��ȫ���ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�Ϊ1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //��Ӧ���ȼ�Ϊ2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʹ��
  	NVIC_Init(&NVIC_InitStructure);
		
		//��������//����ͨ�Ų�����		
		USART_InitStructure.USART_BaudRate = bound;                    ////������
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   ////���ݳ�8λ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;        ////1λֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;           ////��Ч��
  	USART_InitStructure.USART_HardwareFlowControl =  USART_HardwareFlowControl_None; //����Ӳ��������ʧ��
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //���÷���ʹ�ܣ�����ʹ��
  	
		USART_Init(USART2, &USART_InitStructure);      			//USART_Init��ʼ��                                                                                      
		
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 			//����2�����ж� 
  	USART_Cmd(USART2, ENABLE);                     			//ʹ��USART2                                                                                                  
} 



//USARTx_Send
//���ڷ����ַ���
void USARTx_Send(USART_TypeDef* USARTx, u8 *Data, u8 Len)  
{  
    u8 i = 0;  
    for(i = 0; i < Len; i++)  
    {  
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET);     
        USART_SendData(USARTx, Data[i]);                                                     
    }  
}  

//����2,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt,...)  
{
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}

//****************************************************************************** 
//����2�жϳ���       
//******************************************************************************
//���մ��洮������
//extern int laser;
//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//u16 USART_RX_STA=0;       //����״̬���	  

void USART2_IRQHandler(void)                    //����1�жϷ������
{
    
}

void uart4_init(u32 bound)
	{
	GPIO_InitTypeDef GPIO_Initstructure;
	USART_InitTypeDef USART_Initstructure;
	NVIC_InitTypeDef NVIC_Initstructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//PC10 TX
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_Initstructure);
//PC11 RX
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_Initstructure);

	USART_Initstructure.USART_BaudRate=bound;
	USART_Initstructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Initstructure.USART_Parity=USART_Parity_No;
	USART_Initstructure.USART_StopBits=USART_StopBits_1;
	USART_Initstructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(UART4,&USART_Initstructure);

	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//�����ж�
	
	USART_Cmd(UART4,ENABLE);
	USART_ClearFlag(UART4, USART_FLAG_TC);
	
	NVIC_Initstructure.NVIC_IRQChannel =UART4_IRQn; 
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority =0;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_Initstructure);
}

extern char buf[];


u8 get=0;
u8 s=0;
int flagmv=1;
void UART4_IRQHandler(void)
{
 
	if(USART_GetITStatus(UART4,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		get=USART_ReceiveData(UART4);
		if(get==0x31){buf[s]=get;s++;}
		else if(get==0x32){buf[s]=get;s++;}
		else if(get==0x33){buf[s]=get;s++;}
		if(s>=3) 
		{
			flagmv=0;
			s=0;
		}
	}

}
