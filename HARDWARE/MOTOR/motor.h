#ifndef __motor_h
#define __motor_h
#include "sys.h"

#define PC0(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_0);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define PC1(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_1);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define PC2(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_2);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define PC3(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_3);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define PC4(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_4);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define PC5(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_5);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define PC6(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_6);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_6)
#define PC7(a) if (a) \
     GPIO_SetBits(GPIOC,GPIO_Pin_7);\
     else  \
     GPIO_ResetBits(GPIOC,GPIO_Pin_7)
		 
#define m1_1(a) PC0(a)
#define m1_2(a) PC1(a)
#define m2_1(a) PC2(a)
#define m2_2(a) PC3(a)
#define m3_1(a) PC4(a)
#define m3_2(a) PC5(a)
#define m4_1(a) PC6(a)
#define m4_2(a) PC7(a)

#define FORWARD  1
#define STOP     0
#define BACKWARD 2
		 
void Motor(u8 motornum ,u8 state, u32 v);


void Motor_Config(u16 arr,u16 psc);

void Move_Forward(u32 v1,u32 v3);
void Move_Backward(u32 v1,u32 v3);
void Move_Left(u32 v2,u32 v4);
void Move_Right(u32 v2,u32 v4);
void Stop(void);

void Motor_Test(u32 v);

#endif
