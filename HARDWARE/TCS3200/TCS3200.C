//颜色
#include "TCS3200.H"
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "TIMER.H"



u8 Rgena,Ggena,Bgena;
u16 Ramount,Gamount,Bamount;
u16 amount=0;
u16 R=0x00,G=0x00,B=0x00;
u8 rgb;
u8 color;
u8 clolr_flag=0;


void tcs3200_init(void) //PA01567
{
	GPIO_InitTypeDef GPIO_InitStructure;  
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7	;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 	/* 推挽输出*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0	;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 	/*上拉输入*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	VCC=1;
	S0=1;
	S1=0;
	

}


/*******************************************
*
*		  白平衡
*
*******************************************/
void whitebalance(void)
{
	TIM5_Cap_Init();
	delay_ms(10);
	
	S2=0;S3=0;//红色通道
//	amount=0;			 //开始计数
	delay_ms(10);
	Rgena = amount;   //求出红色因子      
//	amount=0;

	S2=1;S3=1;//绿色通道
//	amount=0;
	delay_ms(10);
	Ggena = amount;	 //求出绿色因子
//	amount=0;

	S2=0;S3=1;//蓝色通道
//	amount=0;
	delay_ms(10);
	Bgena = amount;	  //求出蓝色因子
//	amount=0;
	S2=1;S3=0;//关闭通道  	  
}  



u16 tcs3200_RED(void)
{
	S2=0;S3=0;
	amount=0;
	delay_ms(10);
	Ramount=(u32) amount*255/Rgena;	 //取R值
	if(Ramount>255) Ramount = 255;
	return Ramount;
}

u16 tcs3200_GREEN(void)
{
	S2=1;S3=1;
	amount=0;
	delay_ms(10);
	Gamount=(u32) amount*255/Ggena;	//取G值
	if(Gamount>255) Gamount = 255;
	return Gamount;
}

u16 tcs3200_BLUE(void)
{
	S2=0;S3=1;
	amount=0;
	delay_ms(10);
	Bamount=(u32) amount*255/Bgena;//取B值
	if(Bamount>255) Bamount = 255;
	return Bamount;
} 




void tcs3200_dat(void)
{
	R=tcs3200_RED();
	G=tcs3200_GREEN();
	B=tcs3200_BLUE();
}


void tcs3200_RGB(void)
{
	rgb=0;
	tcs3200_dat();
	if(B>R &&B>G&&B>100)
	{
		rgb=3;
	}
	else if(G>R &&G>B &&G>100)
	{
		rgb=2;
	}
	else
	{
		rgb=1;	
	}
}
void ave(void)
{
//	color_flag
}






