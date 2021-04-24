/*
TIM3
CH1-PA6
CH2-PA7
CH3-PB0
CH4-PB1()
*/
#include "jixiebi.h"
#include "sys.h"
#include "delay.h"

extern u32 TIM3_Count1,TIM3_Count2,TIM3_Count3;
u8 flag_count1=0,flag_count2=0,flag_count3=0;
void TIM3_Int_Init(u16 arr,u16 psc);void motor_42_pwm(u16 arr,u16 psc);
u8 test1=1,test2=1,test3=1;
u8 f1=1;u8 f2=1;u8 f3=1;
//长度
u8 sensor_test1(void)
{ u8 i;
	for(i=0;i<10;i++){if(flag1 == 1){ delay_us(5); if(flag1 == 1){flag_count1++;}}delay_ms(1);}
	return flag_count1;}
//高度
u8 sensor_test2(void)
{ u8 i;
	for(i=0;i<10;i++){if(flag2 == 1){ delay_us(5); if(flag2 == 1){flag_count2++;}}delay_ms(1);}
	return flag_count2;}
//角度
u8 sensor_test3(void)
{ u8 i;
	for(i=0;i<10;i++){if(flag3 == 1){ delay_us(5); if(flag3 == 1){flag_count3++;}}delay_ms(1);}
	return flag_count3;}

void longth(u32 round1)
{
	DIR1=1;TIM3_Count1=0;motor_42_pwm(71,299);TIM_SetCompare1(TIM3,10);
	while(1){if(TIM3_Count1==round1){	TIM3_Count1=0;TIM_SetCompare1(TIM3,0);break;}}
}
void reset(void)
{
	u8 count = 0;
	TIM3_Int_Init(199,29); motor_42_pwm(71,299);  //
	TIM_SetCompare1(TIM3,9);TIM_SetCompare2(TIM3,9);TIM_SetCompare3(TIM3,9);
	DIR1=0;DIR2=0;DIR3=0;	
	TIM3_Count1=0;TIM3_Count2=0;TIM3_Count3=0;
//	flag_count1 = 0;flag_count2 = 0;flag_count3 = 0;
	while(1){
	  if(sensor_test1() > 8&&test1){TIM_SetCompare1(TIM3,0);count++;test1=0;
    } 
//		if(sensor_test2() > 8&&test2){TIM_SetCompare2(TIM3,0);count++;test2=0;
//		}
		if(count == 2){break;}
		else{flag_count1 = 0;flag_count2 = 0;flag_count3 = 0;}
	}
}
void luo(s32 round1,s32 round2,s32 round3)
{
	u8 count = 0;	u8 f1=1;u8 f2=1;u8 f3=1;
	DIR1=0;DIR2=0;
	if(round3>0) DIR3=0;
	else
	{
		DIR3=1;
		round3*=(-1);
	}
	delay_us(15);
	TIM3_Int_Init(199,29); motor_42_pwm(71,299);  //
	TIM_SetCompare1(TIM3,9);TIM_SetCompare2(TIM3,9);TIM_SetCompare3(TIM3,9);
	
	TIM3_Count1=0;TIM3_Count2=0;TIM3_Count3=0;
//	flag_count1=0;flag_count2=0;flag_count3=0;
	while(1)
	{ while(TIM3_Count1==round1&&f1){TIM_SetCompare1(TIM3,0); TIM3_Count1 = 0;count++;f1=0;
    break;}
		while(TIM3_Count2==round2&&f2){TIM_SetCompare2(TIM3,0); TIM3_Count2 = 0;count++;f2=0;
		break;}
		while(TIM3_Count3==round3&&f3){TIM_SetCompare3(TIM3,0); TIM3_Count3 = 0;count++;f3=0;
		break;}
		if(count == 3){break;}
	}
}

void ti(s32 round1,s32 round2,s32 round3)
{
	u8 count = 0; 	u8 f1=1;u8 f2=1;u8 f3=1;
	DIR1=1;DIR2=1;	
	if(round3>0) DIR3=1;
	else
	{
		DIR3=0;
		round3*=(-1);
	}
	delay_us(15);
	TIM3_Int_Init(199,29); motor_42_pwm(71,599);  //
	TIM_SetCompare1(TIM3,9);TIM_SetCompare2(TIM3,9);TIM_SetCompare3(TIM3,9);
	
	TIM3_Count1=0;TIM3_Count2=0;TIM3_Count3=0;
//	flag_count1=0;flag_count2=0;flag_count3=0;
	while(1)
	{ while(TIM3_Count1==round1&&f1){TIM_SetCompare1(TIM3,0); TIM3_Count1 = 0;count++;f1=0;
    break;}
		while(TIM3_Count2==round2&&f2){TIM_SetCompare2(TIM3,0); TIM3_Count2 = 0;count++;f2=0;
		break;}
		while(TIM3_Count3==round3&&f3){TIM_SetCompare3(TIM3,0); TIM3_Count3 = 0;count++;f3=0;
		break;}
		if(count == 3){break;}
	}
}



void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIM3					 
}



void motor_42_pwm(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructurer;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//长度
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
   //初始化TIM3
	TIM_TimeBaseStructurer.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructurer.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructurer.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructurer.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructurer); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	//高度
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
   //初始化TIM3
	TIM_TimeBaseStructurer.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructurer.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructurer.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructurer.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructurer); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	//偏角
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
   //初始化TIM3
	TIM_TimeBaseStructurer.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructurer.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructurer.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructurer.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructurer); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	//爪子
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
   //初始化TIM3
	TIM_TimeBaseStructurer.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructurer.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructurer.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructurer.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructurer); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	
	TIM_Cmd(TIM3, ENABLE);
}
void zhua(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructurer;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//长度
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟   
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
   //初始化TIM3
	TIM_TimeBaseStructurer.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructurer.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructurer.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructurer.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructurer); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存
	
	TIM_Cmd(TIM2, ENABLE);
}

void shen(s32 round1,s32 round2,s32 round3)
{
	u8 count = 0; 	u8 f1=1;u8 f2=1;u8 f3=1;
	DIR1=1;DIR2=0;	
	if(round3>0) DIR3=1;
	else
	{
		DIR3=0;
		round3*=(-1);
	}
	delay_us(15);
	TIM3_Int_Init(199,29); motor_42_pwm(71,399);  //
	TIM_SetCompare1(TIM3,9);TIM_SetCompare2(TIM3,9);TIM_SetCompare3(TIM3,9);
	
	TIM3_Count1=0;TIM3_Count2=0;TIM3_Count3=0;
//	flag_count1=0;flag_count2=0;flag_count3=0;
	while(1)
	{ while(TIM3_Count1==round1&&f1){TIM_SetCompare1(TIM3,0); TIM3_Count1 = 0;count++;f1=0;
    break;}
		while(TIM3_Count2==round2&&f2){TIM_SetCompare2(TIM3,0); TIM3_Count2 = 0;count++;f2=0;
		break;}
		while(TIM3_Count3==round3&&f3){TIM_SetCompare3(TIM3,0); TIM3_Count3 = 0;count++;f3=0;
		break;}
		if(count == 3){break;}
	}
}
void suo(s32 round1,s32 round2,s32 round3)
{
	u8 count = 0; 	u8 f1=1;u8 f2=1;u8 f3=1;
	DIR1=0;DIR2=1;	
	if(round3>0) DIR3=1;
	else
	{
		DIR3=0;
		round3*=(-1);
	}
	delay_us(15);
	TIM3_Int_Init(199,29); motor_42_pwm(71,399);  //
	TIM_SetCompare1(TIM3,9);TIM_SetCompare2(TIM3,9);TIM_SetCompare3(TIM3,9);
	
	TIM3_Count1=0;TIM3_Count2=0;TIM3_Count3=0;
//	flag_count1=0;flag_count2=0;flag_count3=0;
	while(1)
	{ while(TIM3_Count1==round1&&f1){TIM_SetCompare1(TIM3,0); TIM3_Count1 = 0;count++;f1=0;
    break;}
		while(TIM3_Count2==round2&&f2){TIM_SetCompare2(TIM3,0); TIM3_Count2 = 0;count++;f2=0;
		break;}
		while(TIM3_Count3==round3&&f3){TIM_SetCompare3(TIM3,0); TIM3_Count3 = 0;count++;f3=0;
		break;}
		if(count == 3){break;}
	}
}

void DIR_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;				 //PE1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
  GPIO_Init(GPIOE, &GPIO_InitStructure);	

}

void flag_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;				 //PF0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //下拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);	
}

//中断处理函数
void TIM3_IRQHandler(void)
{	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	  TIM3_Count1++;
		TIM3_Count2++;
		TIM3_Count3++;
	}	
}
