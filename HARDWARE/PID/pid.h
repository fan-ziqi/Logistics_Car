#ifndef __pid_h
#define __pid_h
#include "sys.h"

#define PWMA   TIM3->CCR1

void Set_Dir(int m);

int myabs(int a);
void Xianfu_Pwm(void);

int PID_Out(int Encoder,int Target);

#endif
