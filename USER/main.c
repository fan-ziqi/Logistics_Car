#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "motor.h"
#include "usart.h"
#include "sensor.h"
#include "xunji.h"
#include "GM65.H"
#include "jixiebi.h"


//机械臂相关
u32 TIM3_Count1=0;u32 TIM3_Count2=0;u32 TIM3_Count3=0;
u32 round1=2000;u32 round2=2000;u32 round3=2000;
u8 flag=1;

char buf[3]={0};

//扫码相关
u8 h=0;
extern u8 usart_table_get[10];
extern void send_data(void);
char m1,m2,m3;
int mm1,mm2,mm3;

//循迹相关
extern u8 Fcount;
extern u8 Bcount;
extern u8 Lcount;
extern u8 Rcount;

int delay=0;

u8 l,m,r;

extern int flagmv;

void task1(int num)
{
	s32 ang;
	if(num==1) ang=-6100;
	else if (num==2) ang=-8200;
	else if(num==3)
	{
		while(1)
		{
			Move_Backward(50,50);
			if((B3&&B4&&B5)||(B4&&B5&&B6)||(B3&&B4&&B5&&B6)) break;
		}
		Stop();
		ang=-7800;
	}
	zhua(1999,719);
	TIM_SetCompare2(TIM2,120);
	delay_ms(1000);
	luo(3000,1000,ang);
	luo(2500,0,0);
  delay_ms(500);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,150);
	delay_ms(1000);
	ti(3000,1000,ang);
	ti(2500,0,0);
	
	
	
	
	if(num==3)
	{
		while(R4==0){Move_Forward(40,40);}
		Stop();
	}
}


void task2(int num)//14000(mid)  11500(right)    16800(left)
{
	s32 ang;
	if(num==1) ang=16800;
	else if (num==2) ang=14000;
	else if(num==3) ang=11500;
		
	
	zhua(1999,719);
	TIM_SetCompare2(TIM2,150);
	luo(2600,0,0);
	delay_ms(1000);
  ti(2000,2000,ang);
	delay_ms(1000);
	luo(1000,2300,0);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,135);
	delay_ms(1000);
	ti(1000,2300,0);
	luo(0,0,ang);
	luo(2000,2000,0);
	ti(2600,0,0);
	
}

void task3(int num)//14000(mid)  11500(right)    16800(left)
{
	s32 ang;
	if(num==1) ang=16800;
	else if (num==2) ang=14000;
	else if(num==3) ang=11500;
//	luo(3000,0,0);//ti(-3000,0,0)
//	delay_ms(1000);   //ti(-1000,2000,ang)
  shen(1000,2300,ang);
	delay_ms(500);
	luo(500,2300,0);
	zhua(1999,719);
	delay_ms(500);
	TIM_SetCompare2(TIM2,160);
	delay_ms(500);
	ti(0,2300,0);
	ti(500,0,0);
	luo(0,0,ang);
	suo(1000,2300,0);
}

void task32(char num)
{
	if(num==0x31)
{
	TIM_SetCompare2(TIM2,160);
	ti(0,1000,0);
	luo(3900,300,1800);
	luo(500,0,0);
  zhua(1999,719);
	TIM_SetCompare2(TIM2,135);
	delay_ms(500);
	ti(4300,300,0);
	ti(0,0,1800);
	luo(0,1000,0);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,135);
}
if(num==0x32)
{
	
	TIM_SetCompare2(TIM2,160);
	ti(0,1000,0);
	luo(3500,1000,-300);
  zhua(1999,719);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
  ti(3500,1000,0);
	ti(0,0,-300);
	luo(0,1000,0);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,135);
}
if(num==0x33)
{
	TIM_SetCompare2(TIM2,160);
	ti(0,1300,0);
	luo(4000,0,-2300);
  zhua(1999,719);
	shen(300,400,0);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
	ti(4000,0,0);
	suo(300,400,0);
	ti(0,0,-2300);
  luo(0,1300,0);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,135);
}
}
void na()
{
	TIM_SetCompare2(TIM2,125);
	delay_ms(200);
	luo(3800,2800,0);
	delay_ms(100);
	shen(2000,2000,0);
	delay_ms(200);
	TIM_SetCompare2(TIM2,155);
	delay_ms(500);
	suo(2500,2500,0);
	ti(3800,2800,0);
	shen(500,500,0);
}

void task4(int num)//ÕÅ¿ª ¼Ð×¡ ¸´Î»    6100 right  8200 mid  8200 left
{
	
	s32 ang;
	if(num==1) ang=8000;
	else if (num==2) ang=8250;
	
	zhua(1999,719);
	TIM_SetCompare2(TIM2,160);
	delay_ms(500);
	luo(2200,1700,ang);
	luo(2200,0,0);
  delay_ms(500);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
	ti(2200,1700,0);
	ti(0,0,ang);
	ti(2200,0,0);
}

void task41(int num)//ÕÅ¿ª ¼Ð×¡ ¸´Î»    6100 right  8200 mid  8200 left
{
	
	s32 ang;
	if(num==1) ang=8550;
	
	zhua(1999,719);
	TIM_SetCompare2(TIM2,160);
	delay_ms(500);
	luo(2000,1800,ang);
	shen(200,200,0);
	luo(2000,0,0);
  delay_ms(500);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
	suo(200,200,0);
	ti(2000,1800,0);
	ti(0,0,ang);
	ti(2000,0,0);
}

void task42(int num)//ÕÅ¿ª ¼Ð×¡ ¸´Î»    6100 right  8200 mid  8200 left
{
	
	s32 ang;
	if(num==2) ang=7850;
	
	zhua(1999,719);
	TIM_SetCompare2(TIM2,160);
	delay_ms(500);
	luo(2000,1800,ang);
	luo(2000,0,0);
  delay_ms(500);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
	ti(2000,1800,0);
	ti(0,0,ang);
	ti(2000,0,0);
}

void task43(int num)//ÕÅ¿ª ¼Ð×¡ ¸´Î»    6100 right  8200 mid  8200 left
{
	
	s32 ang;
	if(num==3) ang=5650;
	
	zhua(1999,719);
	TIM_SetCompare2(TIM2,160);
	delay_ms(500);
	luo(2000,1600,ang);
	luo(2000,200,0);
	shen(100,100,0);
  delay_ms(500);
	zhua(1999,719);
	TIM_SetCompare2(TIM2,130);
	delay_ms(500);
	ti(2000,1600,0);
	suo(100,100,0);
	ti(0,0,ang);
	ti(2000,200,0);
}


int main(void)
{	
  delay_init();
	uart_init(9600);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	//机械臂
	DIR_Init();
	flag_init();
//	reset();

	//灰度
	Sensor_Front_Init();
  Sensor_Back_Init();
	Sensor_Left_Init();
  Sensor_Right_Init();
	 
	//电机
	Motor_Config(101,1999);
	
	
//	OLED_Init(); 
	
	send_data();   //启动扫描二维码
	zhua(1999,719);
	 
	

delay_ms(1000);
	

	while(1){
		
		
//	  oled_show();
//		
		
		
		Move_Left(45,45);
		for(delay=0;delay<10;delay++) delay_ms(100);
		Move_Left(0,0);
		while(L5==0)
		{
		Move_Forward(50,50);
		}
//		for(delay=0;delay<8;delay++) delay_ms(100);
//		Move_Forward(60,30);
//		delay_ms(500);
		Move_Forward(0,0);
			Stop();
			delay_ms(200);

		
		while(Left_Count(70)<2){}
			zero();
			Stop();
			delay_ms(200);
			
		while(F4==0){Move_Right(40,40);}
			Stop();
			delay_ms(200);
			
		Move_Forward(50,50);
		delay_ms(500);
			Stop();
			delay_ms(200);
		
		
		
		while(Front_Count(80)<1){}
			zero();
			Stop();
			delay_ms(1000);
			
			Move_Forward(40,40);
		delay_ms(200);
			Stop();
			delay_ms(200);
		
		
		while(Front_Count(80)<4){}
			zero();
			Stop();
			delay_ms(200);
			
		while(R4==0){Move_Backward(40,40);}
			Stop();
			delay_ms(200);
			
		Move_Right(40,40);
		delay_ms(500);
			Stop();
			delay_ms(200);
		
		uart4_init(9600);

		while(flagmv) delay_ms(50);
		
		l=buf[0];
		m=buf[1];
		r=buf[2];
		
		mm1=usart_table_get[0];
	  mm2=usart_table_get[1];
	  mm3=usart_table_get[2];
		
		mm1=0x32;
		mm2=0x33;
		mm3=0x31;
		

		while(1)
		{
			Track_Right(40);
			if((R3&&R4&&R5)||(R4&&R5&&R6)||(R3&&R4&&R5&&R6)) break;
		}
		Move_Right(40,40);
		delay_ms(500);
		while(1)
		{
			Track_Right(40);
			if((R3&&R4&&R5)||(R4&&R5&&R6)||(R3&&R4&&R5&&R6)) break;
		}

//		Move_Right(20,20);
//		delay_ms(100);
		
		Stop();
		
		delay_ms(500);
		
		luo(0,0,7000);
		zhua(1999,719);
		TIM_SetCompare2(TIM2,120);
		delay_ms(1000);
		
		
		//1
		
		if(l==mm1)task1(1);
		if(m==mm1)task1(2);
		if(r==mm1)task1(3);
		task2(1);
		
		if(l==mm2)task1(1);
		if(m==mm2)task1(2);
		if(r==mm2)task1(3);
		task2(2);
		
		if(l==mm3)task1(1);
		if(m==mm3)task1(2);
		if(r==mm3)task1(3);
		task2(3);

//		
//		
//		
//		
//		//1
//		
//		





///









		while(Left_Count(70)<3){}
			zero();
			Stop();
			delay_ms(200);
			
		while(B4==0){Move_Right(40,40);}
			Stop();
			delay_ms(200);
			
		Move_Backward(40,40);
		delay_ms(500);
			Stop();
			delay_ms(200);
		
		
//		
		while(Back_Count(70)<1){}
			zero();
			Stop();
			delay_ms(200);
			
		while(L4==0){Move_Forward(40,40);}
			Stop();
			delay_ms(200);
			
		
		
		delay_ms(1000);
		
		buf[0]=0;
		buf[1]=0;
		buf[2]=0;
		
		luo(4000,3000,0);
		
		uart4_init(9600);

		flagmv=1;
		
		while(flagmv) delay_ms(50);
		
		l=buf[0];
		m=buf[1];
		r=buf[2];
		//ceshi
		m1=usart_table_get[0];
	  m2=usart_table_get[1];
	  m3=usart_table_get[2];
		
		m1=0x32;
		m2=0x33;
		m3=0x31;
		//
		
//		//OPENMV
ti(4000,3000,0);
//		
		while(1)
		{
			Track_Front(40);
			if((B3&&B4&&B5)||(B4&&B5&&B6)||(B3&&B4&&B5&&B6)) break;
		}
		Move_Forward(40,40);
		delay_ms(500);
		while(1)
		{
			Track_Front(40);
			if((B3&&B4&&B5)||(B4&&B5&&B6)||(B3&&B4&&B5&&B6)) break;
		}
		Stop();
		delay_ms(100);
		while(1)
		{
			Move_Backward(40,40);
			if((B3&&B4&&B5)||(B4&&B5&&B6)||(B3&&B4&&B5&&B6)) break;
		}
		
		Stop();
		delay_ms(200);
		

		

		
//		//task3
		
		task3(1);
		task32(m1);
		task3(2);
		task32(m2);
		task3(3);
		task32(m3);
		
		
		
		//z
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		//renwu2


		while(1)
		{
			Move_Backward(50,50);
			if(L1) break;
		}
		Stop();
		Move_Forward(40,40);
		delay_ms(300);
		Stop();
		
		na();
		task2(1);
		
		while(1)
		{
			Move_Left(35,35);
			if((L3&&L4&&L5)||(L4&&L5&&L6)||(L3&&L4&&L5&&L6)) break;
		}
		Stop();
		
		na();
		task2(2);
		
		Move_Right(40,40);
		delay_ms(500);
		
		while(1)
		{
			Move_Right(40,40);
			if((R3&&R4&&R5)||(R4&&R5&&R6)||(R3&&R4&&R5&&R6)) break;
		}
		Stop();
		
		na();
		task2(3);
		
		
		
		
//		
//		//renwu3
//		
		delay_ms(2000);
		
		
		Move_Backward(50,50);
		delay_ms(500);
		Stop();
		Move_Left(40,40);
		delay_ms(400);
			Stop();
			delay_ms(200);
//		
//		
//		
//		
		while(Left_Count(60)<3){}
			zero();
			Stop();
			delay_ms(200);
			
		while(B5==0){Move_Right(40,40);}
			Stop();
			delay_ms(200);
			
		Move_Backward(50,50);
		delay_ms(500);
			Stop();
			delay_ms(200);
//		
//		
//		
//		
////		
////		//2
////		
////		
		while(Back_Count(70)<2){}
			zero();
			Stop();
			delay_ms(200);
			
		while(L4==0){Move_Forward(40,40);}
			Stop();
			delay_ms(200);		

//		
		while(1)
		{
			Track_Left(40);
			if((L3&&L4&&L5)||(L4&&L5&&L6)||(L3&&L4&&L5&&L6)) break;
		}
		Stop();
		delay_ms(100);
		while(1)
		{
			Move_Right(40,40);
			if((L3&&L4&&L5)||(L4&&L5&&L6)||(L3&&L4&&L5&&L6)) break;
		}
		Stop();
		delay_ms(100);
		
		Move_Left(40,40);
		delay_ms(200);
		Stop();
////		
		
		
		delay_ms(1000);
		
		
		
		if(m==0x31)
		{
			while(1)
		{
			Move_Backward(50,50);
			if((F3&&F4&&F5)||(F4&&F5&&F6)||(F3&&F4&&F5&&F6)) break;
		}
		Stop();
			task3(1);
			task41(1);
				while(1)
		{
			Move_Forward(50,50);
			if(R4) break;
		}
		Stop();
		}
		if(m==0x32) 
		{
			task3(1);
			task42(2);
		}
		if(m==0x33) 
		{
			task3(1);
			task43(3);
		}
		//
		if(l==0x31)
		{
			while(1)
		{
			Move_Backward(50,50);
			if((F3&&F4&&F5)||(F4&&F5&&F6)||(F3&&F4&&F5&&F6)) break;
		}
		Stop();
			task3(2);
			task41(1);
		while(1)
		{
			Move_Forward(50,50);
			if(R4) break;
		}
		Stop();
		}
		if(l==0x32) 
		{
			task3(2);
			task42(2);
		}
		if(l==0x33) 
		{
			task3(2);
			task43(3);
		}
		//
		if(r==0x31)
		{
			while(1)
		{
			Move_Backward(50,50);
			if((F3&&F4&&F5)||(F4&&F5&&F6)||(F3&&F4&&F5&&F6)) break;
		}
		Stop();
			task3(3);
			task41(1);
		while(1)
		{
			Move_Forward(50,50);
			if(R4) break;
		}
		Stop();
		}
		if(r==0x32) 
		{
			task3(3);
			task42(2);
		}
		if(r==0x33) 
		{
			task3(3);
			task43(3);
		}
		
		
		
		  while(B4==0){Move_Right(40,40);}
			Stop();
			delay_ms(200);
			
			Move_Backward(50,50);
			delay_ms(300);
			Stop();
			delay_ms(200);
		
		
		
		
		
		
		
		
		
		
		
		
		
//		
//		
//		
//		
		while(Back_Count(70)<3){}
			zero();
			Stop();
			for(delay=0;delay<10;delay++) delay_ms(100);
			
			
			while(L4==0){Move_Forward(40,40);}
			Stop();
			delay_ms(200);
			
		Move_Left(50,50);
		delay_ms(500);
			Stop();
			delay_ms(200);
			
			while(Left_Count(50)<1){}
			zero();
			Stop();
			for(delay=0;delay<10;delay++) delay_ms(100);

			
			
		
			
		while(1)
		{
			Move_Left(30,30);
			if(L8||L7) break;
		}
			Stop();
			delay_ms(200);	
			
		while(1)
		{
			Move_Backward(40,40);
			if((F3&&F4&&F5&&F6)||(F3&&F4&&F5)||(F4&&F5&&F6)||(F3&&F4)||(F4&&F5)||(F5&&F6)) break;
		}
			Stop();
			delay_ms(200);	
//			
//			
//			
			
			
		while(1)
		{
			Stop();
		}
		
 }
}
 
