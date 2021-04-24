#ifndef  __TCS3200_H
#define  __TCS3200_H
#include "stm32f10x.h" 
#include "sys.h"


#define VCC PAout(13)
#define S0 PAout(1)
#define S1 PAout(5)
#define S2 PAout(6)
#define S3 PAout(7)




void tcs3200_init(void);
void whitebalance(void);
u16 tcs3200_RED(void);
u16 tcs3200_GREEN(void);
u16 tcs3200_BLUE(void);

void tcs3200_dat(void);
void tcs3200_RGB(void);

#endif









