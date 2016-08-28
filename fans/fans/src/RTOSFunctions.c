/*
* RTOSFunction.c
*
* File that contains all different tasks
* which makes the program
*
* Authors: Karl Mösenbacher & Carl Öström
*/

#include <asf.h>
#include "RTOSFunctions.h"
#include "NavigationFunctions.h"
#include "BackControllerFunctions.h"
#include "FrontControllerFunctions.h"

xSemaphoreHandle SemaphoreControl = 0;

/* Initialize semaphores */
void InitSemaphores(void){
	vSemaphoreCreateBinary(SemaphoreControl);
}

/* Initialize all three processes and start scheduling*/
void InitProcess(void){
	
	/* Process for handling the navigation - unit */
	if(xTaskCreate(TaskNavigation,(const signed char * const) "Navigation", 1024,NULL, 3, NULL) !=pdPASS){
		printf("Could not create process navigation\n\r");
	}
	
	/* Process for handling the front controller */
	if(xTaskCreate(TaskFrontController,(const signed char * const) "Front controller", 1024,NULL, 2, NULL) !=pdPASS){
		printf("Could not create process start_controller_top\n\r");
	}
	
	/* Process for handling the back controller */
	if(xTaskCreate(TaskBottomController,(const signed char * const) "Back controller", 1024,NULL, 1, NULL) !=pdPASS){
		printf("Could not create process start_controller_top\n\r");
	}
	
	/* Start Scheduler */
	vTaskStartScheduler();
}