#ifndef __jixiebi_h
#define __jixiebi_h
#include "sys.h"

void motor_42_pwm(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void zhua(u16 arr,u16 psc);
void shen(s32 round1,s32 round2,s32 round3);
void suo(s32 round1,s32 round2,s32 round3);

void DIR_Init(void);
void flag_init(void);

void longth(u32 round1);
void height(u32 round2);
void angle(u32 round3);

void reset(void);
void luo(s32 round1,s32 round2,s32 round3);
void ti(s32 round1,s32 round2,s32 round3);
#define DIR1  PEout(1)  //长度
#define DIR2  PEout(2)  //高度
#define DIR3  PEout(3)  //角度

#define flag1 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0)//长度
#define flag2 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1)//高度
#define flag3 GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2)//角度


#endif

