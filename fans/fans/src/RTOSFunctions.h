/*
* RTOSFunction.h
*
* Authors: Karl M�senbacher & Carl �str�m
*/


#ifndef RTOSFUNCTIONS_H_
#define RTOSFUNCTIONS_H_


extern xSemaphoreHandle SemaphoreControl;

void InitSemaphores(void);
void InitProcess(void);

#endif /* RTOSFUNCTIONS_H_ */