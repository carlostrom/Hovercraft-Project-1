/*
* FrontControllerFunctions.c
*
* File that contains functions that calculates
* new PWM signals with a PD-controller for both front fans.
*
* Authors: Karl Mösenbacher & Carl Öström
*/

#include <asf.h>
#include "FrontControllerFunctions.h"
#include "RTOSFunctions.h"
#include "PWMFunctions.h"
#include "LookUpTableFunctions.h"
#include "NavigationFunctions.h"


/* Variables for PD-controller */
static double KP = 2.5;
static double TD = 1.3;
double dTFront = 0.1;
double eFrontDiff = 0;


/* Variables for front left PD-controller */
static int eFrontLeftSum[2] = {0};
int DutyCycleFrontLeft = 0;


/* Variables for front right PD-controller */
static int eFrontRightSum[2] = {0};
int DutyCycleFrontRight = 0;


void TaskFrontController(void *p)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		int SampleTimeSempaphor = 100;
		xSemaphoreTake(SemaphoreControl,portMAX_DELAY);
		
		/* Evaluate side to control */
		FrontControllerEvaluator();
		/* Change Duty cycle on both front fans */
		PWMSetDutyCycleFront(DutyCycleFrontRight,DutyCycleFrontLeft);
		
		xSemaphoreGive(SemaphoreControl);
		vTaskDelayUntil(&xLastWakeTime,SampleTimeSempaphor);
	}
}


/* Function that evaluate which side (left or right) front controller to use */
void FrontControllerEvaluator(void)
{
	/* Subtracting both sides sensors current distance to the magnetic field */
	int DistanceDiff = (int)CurrentValuesTable[0]-(int)CurrentValuesTable[1];
	
	if (DistanceDiff>0)
	{
		FrontLeftController(DistanceDiff);
		DutyCycleFrontRight = 260;
	}
	else if (DistanceDiff<0)
	{
		FrontRightController(DistanceDiff);
		DutyCycleFrontLeft = 0;
		} else {
		/* Calculated duty cycle so the hovercraft wont start spinning */
		DutyCycleFrontRight = 260;
		DutyCycleFrontLeft = 0;
	}
}


/* PD-controller for front left fan */
void FrontLeftController(int DistanceDiff)
{
	double eFrontLeft;
	
	/* Lefts fan deviation against the right fan */
	eFrontLeft =  (double)DistanceDiff;

	/*  Calculate difference in deviation */
	eFrontLeftSum[1] = eFrontLeftSum[0] + eFrontLeft;
	eFrontDiff = eFrontLeftSum[1] - eFrontLeftSum[0];
	
	/* Calculate front left fans duty cycle */
	DutyCycleFrontLeft = KP * (eFrontLeft  + (TD/dTFront * eFrontDiff));
	DutyCycleFrontLeft = (int)DutyCycleFrontLeft;

	eFrontLeftSum[0] = eFrontLeftSum[1];
	
	/* Make sure duty cycle wont get values over or under its resolution */
	if(DutyCycleFrontLeft >800){
		DutyCycleFrontLeft = 800;
	}
	if(DutyCycleFrontLeft < 200){
		DutyCycleFrontLeft = 200;
	}
}


/* PD-controller for front right fan */
void FrontRightController(int DistanceDiff)
{
	double eFrontRight;
	
	/* Front rights fan deviation against the left fan */
	eFrontRight = (double)(DistanceDiff * -1);
	
	/*  Calculate difference in deviation */
	eFrontRightSum[1] = eFrontRightSum[0] + eFrontRight;
	eFrontDiff = eFrontRightSum[1] - eFrontRightSum[0];
	
	/* Calculate front right fans duty cycle */
	DutyCycleFrontRight =  KP * (eFrontRight + TD/dTFront * eFrontDiff );
	DutyCycleFrontRight = (int)DutyCycleFrontRight;
	
	eFrontRightSum[0] = eFrontRightSum[1];

	/* Make sure duty cycle wont get values over or under its resolution */
	if(DutyCycleFrontRight > 800){
		DutyCycleFrontRight = 800;
	}
	if(DutyCycleFrontRight < 220){
		DutyCycleFrontRight = 220;
	}
}