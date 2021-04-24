//扫码 PA9-10
#include "GM65.H"
#include "sys.h"
#include "usart.h"
#include "string.h"

u8 a=0;
u8 i;
u8 j=0;

u8 usart_table_send[]={0x7E, 0x00, 0x08 ,0x01 ,0x00 ,0x02 ,0x01 ,0xAB ,0xCD};   //命令触发模式 触发串口扫描模式
u8 usart_table_get[10];
u8 DATA_ASCII;

void send_data(void)
{
	if(a==0)
	{
//		USART_SendData(USART1, usart_table_send[i]);
		for(i=0;i<9;i++)
		{
			USART_SendData(USART1, usart_table_send[i]);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);  //检测是否发送完毕
			a=1;	
			memset(usart_table_get,0,sizeof(usart_table_get));			//清空结构体
		}
	}	
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{

#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.  （如果有操作系统，作用为保护串口通讯不被更高级的中断打断）
	OSIntEnter();    
#endif

	
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET) 
	{
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE); //读取数据寄存器非空
		DATA_ASCII = USART_ReceiveData(USART1);
		
//		if(DATA_ASCII!=0x0a&&DATA_ASCII!=0x0d)
//		{
			
			if(DATA_ASCII==0X31)
			{
				usart_table_get[j]=DATA_ASCII;
				j++;
			}	

			else if(DATA_ASCII==0X32)
			{
				usart_table_get[j]=DATA_ASCII;	
				j++;			
			}
			else if(DATA_ASCII==0X33)
			{
				usart_table_get[j]=DATA_ASCII;	
				j++;
			}
//		}


//	switch(DATA_ASCII)
//			{
//				case 0x31:
//					usart_table_get[0]=DATA_ASCII;	
//					j++;
//					break;
//				
//				case 0x32:	
//					usart_table_get[1]=DATA_ASCII;
//					j++;
//					break;
//				
//				case 0x33:	
//					usart_table_get[2]=DATA_ASCII;
//					j++;
//					break;			
//			}	


	}	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 


