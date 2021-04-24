#include "xunji.h"
#include "sensor.h"
#include "motor.h"
#include "delay.h"

u8 Fcount=0;
u8 Bcount=0;
u8 Lcount=0;
u8 Rcount=0;

void zero(void)
{
	Fcount=0;
	Bcount=0;
	Lcount=0;
	Rcount=0;
}

int Track_Front(int v)
{
		int flag=1;
    // 车偏右
    if     (F2) Move_Forward(S2_VL,S2_VR);
		else if(F3) Move_Forward(S3_VL,S3_VR);
		else if(F4) Move_Forward(S4_VL,S4_VR);
//		else if(F1) Move_Forward(S1_VL,S1_VR);

		// 车偏左
    else if(F5) Move_Forward(S5_VL,S5_VR);
		else if(F6) Move_Forward(S6_VL,S6_VR);
		else if(F7) Move_Forward(S7_VL,S7_VR);
//		else if(F8) Move_Forward(S8_VL,S8_VR);

    // 其他情况直行
    else        Move_Forward(v,v);
		
		//数线
		if(L4) flag=0;
		return flag;
}

int Track_Back(int v)
{
		int flag=1;
    // 车偏右
    if     (B2) Move_Backward(S2_VL,S2_VR);
		else if(B3) Move_Backward(S3_VL,S3_VR);
		else if(B4) Move_Backward(S4_VL,S4_VR);
//		else if(B1) Move_Backward(S1_VL,S1_VR);

		// 车偏左
    else if(B5) Move_Backward(S5_VL,S5_VR);
		else if(B6) Move_Backward(S6_VL,S6_VR);
		else if(B7) Move_Backward(S7_VL,S7_VR);
//		else if(B8) Move_Backward(S8_VL,S8_VR);

    // 其他情况直行
    else        Move_Backward(v,v);

		//数线
		if(L4) flag=0;
		return flag;
}

int Track_Left(int v)
{
		int flag=1;
    // 车偏右
    if     (L2) Move_Left(S2_VL,S2_VR);//这里就是差速部分，Moveleft就是把参考系变一下，相当于向前的速度，两个参数就是差速
		else if(L3) Move_Left(S3_VL,S3_VR);
		else if(L4) Move_Left(S4_VL,S4_VR);
//		else if(L1) Move_Left(S1_VL,S1_VR);

		// 车偏左
    else if(L5) Move_Left(S5_VL,S5_VR);
		else if(L6) Move_Left(S6_VL,S6_VR);
		else if(L7) Move_Left(S7_VL,S7_VR);
//		else if(L8) Move_Left(S8_VL,S8_VR);

    // 其他情况直行
    else        Move_Left(v,v);
		
		//数线
		if(B4) flag=0;
		return flag;

}

int Track_Right(int v)
{
		int flag=1;
    // 车偏右
    if     (R2) Move_Right(S2_VL,S2_VR);
		else if(R3) Move_Right(S3_VL,S3_VR);
		else if(R4) Move_Right(S4_VL,S4_VR);
//		else if(R1) Move_Right (S1_VL,S1_VR);

		// 车偏左
    else if(R5) Move_Right(S5_VL,S5_VR);
		else if(R6) Move_Right(S6_VL,S6_VR);
		else if(R7) Move_Right(S7_VL,S7_VR);
//		else if(R8) Move_Right(S8_VL,S8_VR);

    // 其他情况直行
    else        Move_Right(v,v);
		
		//数线
		if(B4) flag=0;
		return flag;
}


int Front_Count(int v)
{
	while(Track_Front(v)){}
	Move_Forward(v,v);
	delay_ms(200);
	Fcount+=1;
	return Fcount;
}
int Back_Count(int v)
{
	while(Track_Back(v)){}
	Move_Backward(v,v);
	delay_ms(200);
	Bcount+=1;
	return Bcount;
}
int Left_Count(int v)
{
	while(Track_Left(v)){}
	Move_Left(v,v);
	delay_ms(200);
	Lcount+=1;
	return Lcount;
}
int Right_Count(int v)
{
	while(Track_Right(v)){}
	Move_Right(v,v);
	delay_ms(200);
	Rcount+=1;
	return Rcount;
}
