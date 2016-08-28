/*
* RTOSFunction.h
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#ifndef RTOSFUNCTIONS_H_
#define RTOSFUNCTIONS_H_


extern xSemaphoreHandle SemaphoreControl;

void InitSemaphores(void);
void InitProcess(void);

#endif /* RTOSFUNCTIONS_H_ */