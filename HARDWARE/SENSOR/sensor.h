#ifndef __sensor_h
#define	__sensor_h   

#define F1 PDin(8)
#define F2 PDin(9)
#define F3 PDin(10)
#define F4 PDin(11)
#define F5 PDin(12)
#define F6 PDin(13)
#define F7 PDin(14)
#define F8 PDin(15)

#define B1 PEin(8)
#define B2 PEin(9)
#define B3 PEin(10)
#define B4 PEin(11)
#define B5 PEin(12)
#define B6 PEin(13)
#define B7 PEin(14)
#define B8 PEin(15)

#define L1 PFin(8)
#define L2 PFin(9)
#define L3 PFin(10)
#define L4 PFin(11)
#define L5 PFin(12)
#define L6 PFin(13)
#define L7 PFin(14)
#define L8 PFin(15)

#define R1 PGin(8)
#define R2 PGin(9)
#define R3 PGin(10)
#define R4 PGin(11)
#define R5 PGin(12)
#define R6 PGin(13)
#define R7 PGin(14)
#define R8 PGin(15)


void Sensor_Front_Init(void);
void Sensor_Back_Init(void);
void Sensor_Left_Init(void);
void Sensor_Right_Init(void);

#endif 
