#include "show.h"
  /**************************************************************************
 
 
**************************************************************************/
//unsigned char i;          //计数变量
//unsigned char Send_Count; //串口需要发送的数据个数
//float Vol;
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
		//=============第一行显示小车模式=======================//	
	OLED_ShowString(0,0,"helloworld");
	OLED_ShowNumber(70,10,8,5,12);
	
	
	  //=============第二行显示温度和距离===============//	
//													OLED_ShowNumber(0,10,Temperature/10,2,12);
//													OLED_ShowNumber(23,10,Temperature%10,1,12);
//													OLED_ShowString(13,10,".");
//													OLED_ShowString(35,10,"`C");
//													OLED_ShowNumber(70,10,(u16)Distance,5,12);
//			                    OLED_ShowString(105,10,"mm");
		//=============第三行显示编码器1=======================//	
//		                      OLED_ShowString(00,20,"EncoLEFT");
//		if( Encoder_Left<0)		OLED_ShowString(80,20,"-"),
//		                      OLED_ShowNumber(95,20,-Encoder_Left,3,12);
//		else                 	OLED_ShowString(80,20,"+"),
//		                      OLED_ShowNumber(95,20, Encoder_Left,3,12);
  	//=============第四行显示编码器2=======================//		
//		                      OLED_ShowString(00,30,"EncoRIGHT");
//		if(Encoder_Right<0)		  OLED_ShowString(80,30,"-"),
//		                      OLED_ShowNumber(95,30,-Encoder_Right,3,12);
//		else               		OLED_ShowString(80,30,"+"),
//		                      OLED_ShowNumber(95,30,Encoder_Right,3,12);	
//		//=============第五行显示电压=======================//
//		                      OLED_ShowString(00,40,"Volta");
//		                      OLED_ShowString(58,40,".");
//		                      OLED_ShowString(80,40,"V");
//		                      OLED_ShowNumber(45,40,Voltage/100,2,12);
//		                      OLED_ShowNumber(68,40,Voltage%100,2,12);
//		 if(Voltage%100<10) 	OLED_ShowNumber(62,40,0,2,12);
//		//=============第六行显示角度=======================//
//		                      OLED_ShowString(0,50,"Angle");
//		if(Angle_Balance<0)		OLED_ShowNumber(45,50,Angle_Balance+360,3,12);
//		else					        OLED_ShowNumber(45,50,Angle_Balance,3,12);
		//=============刷新=======================//
		OLED_Refresh_Gram();	
	}

	
