#include "sys.h"
#include "usart.h"	
#include "stdarg.h"
#include "string.h"
#include "delay.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目

  
//void uart_init(u32 bound)//
//{
//  //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
//   
//  //USART1_RX	  GPIOA.10初始化
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

//  //Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//  
//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//串口波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART1, ENABLE);                    //使能串口1 

//}
extern int dirx,diry;
extern u8 hmi_rcv,finish_flag;
//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	 if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//    {
//			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//			hmi_rcv = USART_ReceiveData(USART1);
//			finish_flag=0;dirx=0;diry=0;delay_ms(500);
//    }
//}



#endif

//串口2缓冲区
u8 USART2_RX_BUF[USART_REC_LEN] ;           
u8 USART2_TX_BUF[USART_REC_LEN] ;           

//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	  
 

//******************************************************************************              
//name:             USART2_Init             
//introduce:        USART2初始化        
//****************************************************************************** 
void uart2_init(u32 bound)//laser
{
		GPIO_InitTypeDef GPIO_InitStructure;   //声明一个结构体变量，用来初始化GPIO
  	USART_InitTypeDef USART_InitStructure;   //串口结构体定义
		NVIC_InitTypeDef NVIC_InitStructure;  //中断结构体定义
 
  	//开启GPIOA，USART2 时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  	
		//配置GPIO的模式和IO口 TX     
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;          //串口输出PA2                                                                                          
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
  	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化串口输入
		//RX
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;          //串口输入PA3                                                                              
  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;//浮空输入
  	GPIO_Init(GPIOA,&GPIO_InitStructure);       			 //初始化串口输出
			
		//NVIC 配置
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);             //设置中断优先级分组
  	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;           //打开USART2的全局中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级为1
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          //响应优先级为2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能
  	NVIC_Init(&NVIC_InitStructure);
		
		//串口配置//设置通信波特率		
		USART_InitStructure.USART_BaudRate = bound;                    ////波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;   ////数据长8位
		USART_InitStructure.USART_StopBits = USART_StopBits_1;        ////1位停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;           ////无效验
  	USART_InitStructure.USART_HardwareFlowControl =  USART_HardwareFlowControl_None; //设置硬件流控制失能
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  //设置发送使能，接收使能
  	
		USART_Init(USART2, &USART_InitStructure);      			//USART_Init初始化                                                                                      
		
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 			//串口2接收中断 
  	USART_Cmd(USART2, ENABLE);                     			//使能USART2                                                                                                  
} 



//USARTx_Send
//串口发送字符串
void USARTx_Send(USART_TypeDef* USARTx, u8 *Data, u8 Len)  
{  
    u8 i = 0;  
    for(i = 0; i < Len; i++)  
    {  
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) != SET);     
        USART_SendData(USARTx, Data[i]);                                                     
    }  
}  

//串口2,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u2_printf(char* fmt,...)  
{
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
}

//****************************************************************************** 
//串口2中断程序       
//******************************************************************************
//接收储存串口数据
extern int laser;
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//u16 USART_RX_STA=0;       //接收状态标记	  

void USART2_IRQHandler(void)                    //串口1中断服务程序
{
    u8 Res;    
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
    {
			Res =USART_ReceiveData(USART2);    //读取接收到的数据
			USART_RX_BUF[USART_RX_STA]=Res ;
			if(USART_RX_BUF[0]==0x80)
			{
				USART_RX_STA++;
				if( USART_RX_STA>2 )
				{
					if((USART_RX_BUF[1]==0x06) && (USART_RX_BUF[2]==0x83))
					{
						if(USART_RX_STA>=USART_REC_LEN) 
						{    
							USART_RX_STA=0;    
							if( (USART_RX_BUF[3]<0x34) && (USART_RX_BUF[3]!='E') && (USART_RX_BUF[4]!='R') && (USART_RX_BUF[5]!='R') && (USART_RX_BUF[10] == (u8)(~(0x80+0x06+0x83+USART_RX_BUF[3]+USART_RX_BUF[4]+USART_RX_BUF[5]+0x2E+USART_RX_BUF[7]+USART_RX_BUF[8]+USART_RX_BUF[9])+1)) ) 
							{                
								laser = (USART_RX_BUF[4]-0x30)*10000+(USART_RX_BUF[5]-0x30)*1000 + (USART_RX_BUF[7]-0x30)*100 + (USART_RX_BUF[8]-0x30)*10 + (USART_RX_BUF[9]-0x30);                 
							}
						}
					}
					else USART_RX_STA=0;        
				}            
			} 
			else USART_RX_STA=0;            
    }      
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

	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//接收中断
	
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
void UART4_IRQHandler(void)
{
 
	if(USART_GetITStatus(UART4,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
		get=USART_ReceiveData(UART4);
		if(get==0x31){buf[s]=get;s++;}
		else if(get==0x32){buf[s]=get;s++;}
		else if(get==0x33){buf[s]=get;s++;}
		if(s>=3) s=0;
	}

}

