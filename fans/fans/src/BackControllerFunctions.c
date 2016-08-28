/*
* BackControllerFunctions.c
*
* File that contains functions that calculates
* new PWM signals with a PD-controller for both front fans.
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#include <asf.h>
#include "BackControllerFunctions.h"
#include "RTOSFunctions.h"
#include "PWMFunctions.h"
#include "LookUpTableFunctions.h"
#include "NavigationFunctions.h"


/* Variables for PD-controller */
static double KP = 1.4;
static double TD = 1.2;
double dTBack = 0.1;
double eBackDiff = 0;


/* Variables for back left PD-controller */
static int eBackLeftSum[2] = {0};
int DutyCycleBackLeft = 0;


/* Variables for back right PD-controller */
static int eBackRightSum[2] = {0};
int DutyCycleBackRight = 0;


void TaskBottomController(void *p){
	
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		int SampleTimeSempaphor = 100;
		xSemaphoreTake(SemaphoreControl,portMAX_DELAY);
		
		/* Evaluate side to control */
		BackControllerEvaluator();
		/* Change Duty cycle on both front fans */
		PWMSetDutyCycleBack(DutyCycleBackRight,DutyCycleBackLeft);
		
		xSemaphoreGive(SemaphoreControl);
		vTaskDelayUntil(&xLastWakeTime,SampleTimeSempaphor);
	}
}


/* Function that evaluate which side (left or right) front controller to use */
void BackControllerEvaluator(void)
{
	/* Subtracting both sides sensors current distance to the magnetic field */
	int DistanceDiff = (int)CurrentValuesTable[2] - (int)CurrentValuesTable[3];
	
	if (DistanceDiff>0)
	{
		BackLeftController(DistanceDiff);
		DutyCycleBackRight = 200;
	}
	else if (DistanceDiff<0)
	{
		BackRightController(DistanceDiff);
		DutyCycleBackLeft = 220;
		}else{
		/* Calculated duty cycle so the hovercraft wont start spinning */
		DutyCycleBackRight = 220;
		DutyCycleBackLeft = 0;
	}
}


/* PD-controller for back left fan */
void BackLeftController(int DistanceDiff){
	
	double eBackLeft;
	
	/* Back lefts fan deviation against the Right fan */
	eBackLeft =  (double)DistanceDiff;

	/*  Calculate difference in deviation */
	eBackLeftSum[1] = eBackLeftSum[0] + eBackLeft;
	eBackDiff = eBackLeftSum[1] - eBackLeftSum[0];
	
	/* Calculate back left fans duty cycle */
	DutyCycleBackLeft = KP * (eBackLeft + (TD/dTBack * eBackDiff) );
	DutyCycleBackLeft = (int)DutyCycleBackLeft;
	
	eBackLeftSum[0] = eBackLeftSum[1];
	
	/* Make sure duty cycle wont get values over or under its resolution */
	if(DutyCycleBackRight >800){
		DutyCycleBackRight = 800;
	}
	if(DutyCycleBackRight < 200){
		DutyCycleBackRight = 200;
	}
}


/* PD-controller for back right fan */
void BackRightController(int DistanceDiff)
{
	double eBackRight;
	
	/* Back rights fan deviation against the left fan */
	eBackRight = (double)(DistanceDiff * -1);

	/*  Calculate difference in deviation */
	eBackRightSum[1] = eBackRightSum[0] + eBackRight;
	eBackDiff = eBackRightSum[1] - eBackRightSum[0];
	
	/* Calculate back right fans duty cycle */
	DutyCycleBackRight = KP * (eBackRight + (TD/dTBack * eBackDiff) );
	DutyCycleBackRight = (int)DutyCycleBackRight*0.7;

	eBackRightSum[0] = eBackRightSum[1];

	/* Make sure duty cycle wont get values over or under its resolution */
	if(DutyCycleBackLeft > 800){
		DutyCycleBackLeft = 800;
	}
	if(DutyCycleBackLeft < 210){
		DutyCycleBackLeft = 210;
	}
}