/*
TIM4
CH1-PB6
CH2-PB7
CH3-PB8
CH4-PB9

TIM2
CH1-PA15
CH2-PB3
CH3-PB10
CH4-PB11
*/

#include "stm32f10x.h"
#include "motor.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "sensor.h"

//四个马达的初始化
void Motor_Config(u16 arr,u16 psc)
{	 
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//打开TIM2外设时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//打开TIM4外设时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);  
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); //禁止JTAG功能，把PB3，PB4作为普通IO口使用
	//// GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);   //USART3的复用功能部分重映射 这里要注意，必须要部分重映射USART3否则PB10不能正常输出

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//high?
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);//TIM4的CH1-4为PB6-9
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能的预装载寄存器
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);	//使能定时器1
	TIM_Cmd(TIM4, ENABLE);
	
//	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//TIM2
//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	TIM_OC2Init(TIM2, &TIM_OCInitStructure); 
//	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
//  TIM_ARRPreloadConfig(TIM2, ENABLE);	//使能定时器1
//	TIM_Cmd(TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;  
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           // 复用推挽输出  
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//  GPIO_Init(GPIOA, &GPIO_InitStructure);  
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;  
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PE端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 |GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化

}

void Motor(u8 motornum ,u8 state, u32 v)
{
	switch(motornum)
	{
		case 1:
		{
			switch(state)
			{
				case FORWARD:
				{
					m1_1(1);m1_2(0);
					TIM_SetCompare1(TIM4,v);
					break;
				}
				case BACKWARD:
				{
					m1_1(0);m1_2(1);
					TIM_SetCompare1(TIM4,v);
					break;
				}
				case STOP:
				{
					m1_1(0);m1_2(0);
					TIM_SetCompare1(TIM4,v);
					break;
				}
			}
			break;
		}
		case 2:
		{
			switch(state)
			{
				case FORWARD:
				{
					m2_1(1);m2_2(0);
					TIM_SetCompare2(TIM4,v);
					break;
				}
				case BACKWARD:
				{
					m2_1(0);m2_2(1);
					TIM_SetCompare2(TIM4,v);
					break;
				}
				case STOP:
				{
					m2_1(0);m2_2(0);
					TIM_SetCompare2(TIM4,v);
					break;
				}
			}
			break;
		}
		case 3:
		{
			switch(state)
			{
				case BACKWARD:
				{
					m3_1(1);m3_2(0);
					TIM_SetCompare3(TIM4,v);
					break;
				}
				case FORWARD:
				{
					m3_1(0);m3_2(1);
					TIM_SetCompare3(TIM4,v);
					break;
				}
				case STOP:
				{
					m3_1(0);m3_2(0);
					TIM_SetCompare3(TIM4,v);
					break;
				}
			}
			break;
		}
		case 4:
		{
			switch(state)
			{
				case BACKWARD:
				{
					m4_1(1);m4_2(0);
					TIM_SetCompare4(TIM4,v);
					break;
				}
				case FORWARD:
				{
					m4_1(0);m4_2(1);
					TIM_SetCompare4(TIM4,v);
					break;
				}
				case STOP:
				{
					m4_1(0);m4_2(0);
					TIM_SetCompare4(TIM4,v);
					break;
				}
			}
			break;
		}
	}
}

void Move_Forward (u32 v1,u32 v3)
{
	Motor(1,FORWARD ,v1);
	Motor(3,BACKWARD,v3);
}
void Move_Backward(u32 v1,u32 v3)
{
	Motor(1,BACKWARD,v1);
	Motor(3,FORWARD ,v3);
}
void Move_Left    (u32 v4,u32 v2)
{
	Motor(2,BACKWARD,v2);
	Motor(4,FORWARD ,v4);
}
void Move_Right   (u32 v2,u32 v4)
{
	Motor(2,FORWARD ,v2);
	Motor(4,BACKWARD,v4);
}

void Stop(void)
{
	Motor(1,STOP,0);
	Motor(2,STOP,0);
	Motor(3,STOP,0);
	Motor(4,STOP,0);
}

void Motor_Test(u32 v)
{
	Move_Forward (v,v);
	delay_ms(1000);
	Move_Backward(v,v);
	delay_ms(1000);
	Move_Left    (v,v);
	delay_ms(1000);
	Move_Right   (v,v);
	delay_ms(1000);
}
