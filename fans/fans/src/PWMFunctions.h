/*
* PWMFunctions.h
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#ifndef PWMFUNCTIONS_H_
#define PWMFUNCTIONS_H_


/* Defines for center fan PWM */
#define PWMCENTERPIO			PIOC
#define PWMCENTERPERIPHERAL		PIO_PERIPH_B
#define PWMCENTERPIN			PIO_PC8B_PWML3


/* Defines for back fan PWM */
#define PWMBACKPIO				PIOC
#define PWMBACKPERIPHERAL		PIO_PERIPH_B
#define PWMBACKPIN				PIO_PC23B_PWML6


/* Defines for top right fan PWM */
#define PWMTOPRIGHTPIO			PIOC			
#define PWMTOPRIGHTPERIPHERAL	PIO_PERIPH_B
#define PWMTOPRIGHTPIN			PIO_PC24B_PWML7


/* Defines for top left fan PWM */
#define PWMTOPLEFTPIO			PIOC			
#define PWMTOPLEFTPERIPHERAL	PIO_PERIPH_B	
#define PWMTOPLEFTPIN			PIO_PC22B_PWML5


/* Defines for lower right fan PWM */
#define PWMLOWERRIGHTPIO		PIOC		
#define PWMLOWERRIGHTPERIPHERAL	PIO_PERIPH_B
#define PWMLOWERRIGHTPIN		PIO_PC21B_PWML4		


/* Defines for lower left fan PWM */
#define PWMLOWERLEFTPIO			PIOC
#define PWMLOWERLEFTPERIPHERAL	PIO_PERIPH_B
#define PWMLOWERLEFTPIN			PIO_PC6B_PWML2

	
/* Define for all PWM´s polarity */
#define PWM_POLARITY			PWM_LOW


/* Functions for configuring and initiating */
void PwmConfigure(void);
void PWMClockConfigure(void);
void PWMCenterConfigure(void);
void PWMBackConfigure(void);
void PWMFrontRightConfigure(void);
void PWMFrontLeftConfigure(void);
void PWMBackRightConfigure(void);
void PWMBackLeftConfigure(void);


/* Functions for changing duty cycle */
void PWMSetDutyCycleFront(uint32_t, uint32_t);
void PWMSetDutyCycleBack(uint32_t, uint32_t);


#endif /* PWM_H_ */