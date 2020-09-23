#ifndef _PID_H
#define _PID_H

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	float Out;
}PID;
extern PID Speed_pid, Angle_pid;
void PID_parameter(void);
int Balance_Control(float Pitch,short Gyor_y);
#endif
