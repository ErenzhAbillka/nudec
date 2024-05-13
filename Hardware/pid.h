#ifndef __PID_H
#define __PID_H

typedef struct
{
	float kp;
	float ki;
	float kd;
	float Error;
	float Error_Sum;
	float Error_Last;
} PID;

extern PID pid;

float PID_Down(void);
float PID_Up(void);

#endif
