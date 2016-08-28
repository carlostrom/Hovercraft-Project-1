/*
* NavigationFunctions.h
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#ifndef NAVIGATIONFUNCTIONS_H_
#define NAVIGATIONFUNCTIONS_H_


void TaskNavigation(void*);
void ReadTopValue(uint32_t, uint32_t);
void ReadLowerValue(uint32_t, uint32_t);
void MoveValues(void);
void CreateAverage(void);
void MakeValues(void);


#define BUFFERTSIZE 10


#endif /* NAVIGATIONFUNCTIONS_H_ */