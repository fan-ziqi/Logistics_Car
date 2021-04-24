#include "pid.h"
#include "sys.h"
#include "motor.h"

int sum=0;
//int Target_velocity=50;
extern int Encoder;
extern int Motor;
//extern int Target_velocity;

int PID_Out(int Encoder,int Target)
{
	float Kp = 2,Ki = 40,Kd = 0.04;
	static int Bias,Pwm,Last_bias;
	
	Bias=Target-Encoder;                //计算偏差
	Pwm+=Ki*(Bias-Last_bias)+Kp*Bias+Kd*sum;   //增量式PI控制器
	Last_bias=Bias;	                   //保存上一次偏差 
	sum = sum + Bias;
	return Pwm;
}
void Set_Dir(int m)
{
	if(m>0)
	{
		BIN1=1;
		BIN2=0;
	}
	else
	{
		BIN1=0;
		BIN2=1;
	}
	PWMA=myabs(Motor);
}
void Xianfu_Pwm(void)
{
	int Amplitude=7099;  //===PWM满幅是7200 限制在7100
	if(Motor<-Amplitude)  Motor = -Amplitude;
	if(Motor>Amplitude)   Motor =  Amplitude;
}

int myabs(int a) //取绝对值
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
