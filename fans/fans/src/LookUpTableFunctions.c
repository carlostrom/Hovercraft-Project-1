/*
* LookUpTableFunctions.c
*
* This file contains function that returns a distance
* depending on the latest ADC value also known as a LookUpTable.
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#include <asf.h>
#include "LookUpTableFunctions.h"
#include "NavigationFunctions.h"


/* Extern variable for sharing the results with the different RegulatorFunctions */
uint32_t CurrentValuesTable[4] = {0};

/* Distance */
static uint32_t Distans[25] =  { 0,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,110};

/* ADC values split into four rows that represents values from each sensor */
static uint32_t LockUpTable[4][25] =
{
	{1050,977,985,989,988,984,980,975,960,894,781,702,624,575,533,490,450,420,388,365,340,320,300,282,0}, /* Top left sensor */
	{1050,981,996,999,996,991,988,979,962,905,830,770,715,645,600,544,515,465,435,415,395,360,345,330,0}, /* Top right sensor */
	{1050,984,990,992,991,989,987,983,978,968,897,811,730,667,622,579,530,494,460,427,404,380,356,339,0}, /* Lower left sensor */
	{1050,992,994,993,990,986,980,973,954,884,805,740,675,612,560,513,480,445,413,390,361,341,323,301,0} /* Lower right sensor */
};


/* Get distans out of sensors A/D-converter values */
void InvalueToDistanse(uint32_t CurrentTopLeftValue,uint32_t CurrentTopRightValue,uint32_t CurrentLowerLeftValue,uint32_t CurrentLowerRightValue)
{
	/* Collects the latest ADC values from sensors */
	CurrentValuesTable[0] = CurrentTopLeftValue;
	CurrentValuesTable[1] = CurrentTopRightValue;
	CurrentValuesTable[2] = CurrentLowerLeftValue;
	CurrentValuesTable[3] = CurrentLowerRightValue;
	
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			/* Checks if the ADC values is in range for the LookUpTable for each sensor */
			if((CurrentValuesTable[i] <= LockUpTable[i][j]) && (CurrentValuesTable[i] >= LockUpTable[i][j+1]))
			{
				/* Control which is the nearest ADC value in the LookUpTable */
				if((LockUpTable[i][j] - CurrentValuesTable[i]) < (CurrentValuesTable[i] - LockUpTable[i][j+1]))
				{
					CurrentValuesTable[i] = Distans[j];
					break;
					
					}else{
					CurrentValuesTable[i] = Distans[j+1];
					break;
				}
				
			}
			
		}
	}
}
