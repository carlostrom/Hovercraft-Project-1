/*
* NavigationFunctions.c
*
* This file contains functions that signal process
* read ADC values
*
*  Authors: Karl Mösenbacher & Carl Öström
*/


#include <asf.h>
#include "NavigationFunctions.h"
#include "RTOSFunctions.h"
#include "ADFunctions.h"
#include "LookUpTableFunctions.h"


/* Buffers for every sensor */
static int TopRightBuffer[BUFFERTSIZE] = {0};
static int TopLeftBuffer[BUFFERTSIZE] = {0};
static int LowerRightBuffer[BUFFERTSIZE] = {0};
static int LowerLeftBuffer[BUFFERTSIZE] = {0};


/* Variables for current sensor values */
uint32_t CurrentTopRightValue;
uint32_t CurrentTopLeftValue;
uint32_t CurrentLowerRightValue;
uint32_t CurrentLowerLeftValue;


void TaskNavigation(void *p){
	
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;){
		int SampleTimeSempaphor = 100;
		
		xSemaphoreTake(SemaphoreControl,portMAX_DELAY);
		
		MakeValues();
		
		xSemaphoreGive(SemaphoreControl);
		vTaskDelayUntil(&xLastWakeTime,SampleTimeSempaphor);
	}
}


/* Function that calls for current ADC values and signal processes them */
void MakeValues(void)
{
	/* Read the latest ADC values */
	CurrentTopRightValue = ReadTopRight();
	CurrentTopLeftValue = ReadTopLeft();
	CurrentLowerLeftValue = ReadLowerLeft();
	CurrentLowerRightValue = ReadLowerRight();

	
	MoveValues();
	CreateAverage(); 
	/* Convert values from ADC into distance */
	InvalueToDistanse(CurrentTopLeftValue,CurrentTopRightValue,CurrentLowerLeftValue,CurrentLowerRightValue);
}


/* Function that moves values in a buffer */
void MoveValues(void)
{
	/* Moving top values in both buffers */
	for(int i = BUFFERTSIZE-1; i > 0;i--)
	{
		TopRightBuffer[i] = TopRightBuffer[i-1];
		TopLeftBuffer[i] = TopLeftBuffer[i-1];
		LowerLeftBuffer[i] = LowerLeftBuffer[i-1];
		LowerRightBuffer[i] = LowerRightBuffer[i-1];
	}
	
	/* Adding last read value to first position in buffers */
	TopRightBuffer[0] = CurrentTopRightValue;
	TopLeftBuffer[0] = CurrentTopLeftValue;
	LowerLeftBuffer[0] = CurrentLowerLeftValue;
	LowerRightBuffer[0] = CurrentLowerRightValue;
}


/* Create average for filtering */
void CreateAverage(void){
	
	int TopRightAverage = 0;
	int TopLeftAverage = 0;
	int LowerRightAverage = 0;
	int LowerLeftAverage = 0;
	
	/* Calculate median value for all sensors */
	for(int i = 0; i < BUFFERTSIZE;i++){
		TopRightAverage +=TopRightBuffer[i];
		TopLeftAverage +=TopLeftBuffer[i];
		LowerLeftAverage += LowerLeftBuffer[i];
		LowerRightAverage += LowerRightBuffer[i];
	}
	CurrentTopRightValue =( TopRightAverage / BUFFERTSIZE );
	CurrentTopLeftValue = ( TopLeftAverage / BUFFERTSIZE );
	CurrentLowerLeftValue = ( LowerLeftAverage / BUFFERTSIZE );
	CurrentLowerRightValue = ( LowerRightAverage / BUFFERTSIZE );
}

