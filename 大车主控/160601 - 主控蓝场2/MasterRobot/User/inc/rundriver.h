#ifndef _RUNDRIVER_H
#define _RUNDRIVER_H


#define BluePart      -1              
#define RedPart       1

#define PlacePart   RedPart 

#include "stm32f4xx.h"
#include "math.h"
#include "pwm.h"

#define BeginX       36.135            //29.76        //37.8
#define BeginY       39.7            //41.05        //54.6
#define BeginSixX    90
#define BeginSixY    1330


#define CAN_BUF_NUM         50                            //缓冲指令条数



//结构体声明
typedef struct position
{
		float x;
		float y;
		float angle;              //角度制
}POSITION;

typedef struct speed
{
		float Vx;
		float Vy;
		float Vw;
}SPEED;

typedef struct pointonbezier
{
		float x;
		float y;
		float t;
}POINTONBEZIER;

typedef struct posi
{
		float x;
		float y;
}POSI;

typedef struct motors32
{
	s32 FanHight;
	s32 FanCircle;
	s32 HeartHand;
	s32 SetHeart;
	s32 MotorOne;
	s32 MotorTwo;
	s32 MotorThree;
	s32 MotorFour;
}MOTORS32;

typedef struct motors16
{
	s16 FanHight;
	s16 FanCircle;
	s16 HeartHand;
	s16 SetHeart;
	s16 MotorOne;
	s16 MotorTwo;
	s16 MotorThree;
	s16 MotorFour;
}MOTORS16;

typedef struct motorfloat
{
	float FanHight;
	float FanCircle;
	float HeartHand;
	float SetHeart;
	float MotorOne;
	float MotorTwo;
	float MotorThree;
	float MotorFour;
}MOTORFLOAT;


/*******bezier曲线描述结构体**********/
typedef struct bezierdescribe
{
	POSI P0;			//用户
	POSI P1;			//算出
	POSI P2;			//算出
	POSI P3;			//用户
	float bezier_startangle;		//用户
	float bezier_endangle;			//用户
	float length1;					//用户
	float length2;					//用户
	float x_t3;				//算出
	float x_t2;				//算出
	float x_t1;				//算出
	float x_t0;				//算出
	float y_t3;				//算出
	float y_t2;				//算出
	float y_t1;				//算出
	float y_t0;				//算出
}BEZIER;


typedef struct TypedefPID
{
		float Kp;
		float Ki;
		float Kd; 
		float Esum;
		float E[3];
}PID;

typedef struct Camera
{
		s16   errorcameraline;
		float positionnowy;
}CAMERA;


/* CAN循环队列元素 */ 
typedef struct _Can_Information
{
	u16 StdId;
	u8  DLC;
	u8  Data[8];
	u8  Type;
} Can_Information;


/* CAN待存入发送队列循环队列元素 */ 
typedef struct _Can_Information_NoSend Can_Information_NoSend;
typedef struct _Can_Information_NoSend
{
	u16 StdId;
	u8  DLC;
	u8  Data[8];
	u8  Type;
	Can_Information_NoSend *Next;
} Can_Information_NoSend;

typedef struct __Can_queue
{
   u16 Front;        
   u16 Rear;
   Can_Information CANBUF[CAN_BUF_NUM];
} Can_queue;

//结构体变量声明

extern volatile POSITION PositionNow;
extern volatile POSITION LockPoint;

extern POINTONBEZIER BPoint1;
extern POINTONBEZIER BPoint2;

extern volatile SPEED SpeedNow;
extern SPEED SpeedStart;
extern SPEED SpeedEnd;
extern volatile SPEED SpeedWantSet;
extern volatile SPEED SpeedWantSetOld;
extern volatile SPEED SpeedAbsolute;

extern POSI VectorPosition;
extern POSI VectorError;

extern float DeltaT;

void CalculateWheelSpeedOpposite(SPEED speedwantset,POSITION positionnow);
void CalculateWheelSpeedAbsolute(SPEED speedwantset);

extern int PWM1,PWM2,PWM3,PWM4;

#include "visual_scope.h"

#endif

