/*
* Main.c
*
* This file contains functions that initiate 
* the program units
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#include <asf.h>
#include "RTOSFunctions.h"
#include "ADFunctions.h"
#include "PWMFunctions.h"
#include "ConsoleFunctions.h"


int main (void)
{
	sysclk_init(); /* Initiate system clock */
	board_init(); /* Initiate board */
	InitSemaphores(); /* Initiate Semaphores */
	ADCConfigure(); /* Initiate ADC */
	PwmConfigure(); /* Initiate PWM */
	ConfigureConsole(); /* Initiate terminal */
	InitProcess(); /* Initiate all processes */
}
