#ifndef __xunji_h
#define	__xunji_h   

//#define S1_VL 10
//#define S1_VR 65

#define S2_VL 50
#define S2_VR 100

#define S3_VL 40
#define S3_VR 80

#define S4_VL 50
#define S4_VR 70

#define S5_VL 70
#define S5_VR 50

#define S6_VL 80
#define S6_VR 40

#define S7_VL 100
#define S7_VR 50

//#define S2_VL 50
//#define S2_VR 100

//#define S3_VL 40
//#define S3_VR 90

//#define S4_VL 50
//#define S4_VR 90

//#define S5_VL 90
//#define S5_VR 50

//#define S6_VL 90
//#define S6_VR 40

//#define S7_VL 100
//#define S7_VR 50

//#define S8_VL 65
//#define S8_VR 10


int Track_Front(int v);
int Track_Back (int v);
int Track_Left (int v);
int Track_Right(int v);

int Front_Count(int v);
int Back_Count(int v);
int Left_Count(int v);
int Right_Count(int v);

void zero(void);

#endif 
