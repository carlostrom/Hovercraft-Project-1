/*
* PWMFunctions.c
*
* This file contains functions that initiates and changes
* PWM´s signals and their duty cycle  
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#include <asf.h>
#include <pwm.h>
#include "PWMFunctions.h"


/* PWM instances for all PWM´s */
static pwm_channel_t PWMCenterChannelInstance;
static pwm_channel_t PWMBackChannelInstance;
static pwm_channel_t PWMTopRightChannelInstance;
static pwm_channel_t PWMTopLeftChannelInstance;
static pwm_channel_t PWMLowerRightChannelInstance;
static pwm_channel_t PWMLowerLeftChannelInstance;


/* Function that calls all PWM´s for configure */
void PwmConfigure(void)
{
	PWMClockConfigure();
	PWMCenterConfigure();
	PWMBackConfigure();
	PWMFrontRightConfigure();
	PWMFrontLeftConfigure();
	PWMBackRightConfigure();
	PWMBackLeftConfigure();
}


/* Configure PWM clock */
void PWMClockConfigure(void)
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM,0);
	pwm_channel_disable(PWM,6);
	pwm_clock_t clock_setting = {
		.ul_clka = 1000 * 1000,
		.ul_clkb = 0,
		.ul_mck = 86000000
	};
	pwm_init(PWM, &clock_setting);
}


/* Configure PWM CENTER on Arduino Due digital pin 40 */
void PWMCenterConfigure()
{
	/* Initiate and configure PWM CENTER */
	PWMCenterChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMCenterChannelInstance.polarity = PWM_POLARITY;
	PWMCenterChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMCenterChannelInstance.ul_period = 1000;
	PWMCenterChannelInstance.ul_duty = 625;
	PWMCenterChannelInstance.channel = PWM_CHANNEL_3;
	pwm_channel_init(PWM,&PWMCenterChannelInstance);
	
	/* Configure PWM CENTER output pin*/
	pio_set_peripheral(PWMCENTERPIO, PWMCENTERPERIPHERAL, PWMCENTERPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_3);
}

/* Configure PWM BACK on Arduino Due digital pin 7 */
void PWMBackConfigure(void)
{
	/* Initiate and configure PWM BACK */
	PWMBackChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMBackChannelInstance.polarity = PWM_POLARITY;
	PWMBackChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMBackChannelInstance.ul_period = 1000;
	PWMBackChannelInstance.ul_duty = 325;
	PWMBackChannelInstance.channel = PWM_CHANNEL_6;
	pwm_channel_init(PWM,&PWMBackChannelInstance);
	
	/* Configure PWM BACK output pin*/
	pio_set_peripheral(PWMBACKPIO, PWMBACKPERIPHERAL, PWMBACKPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_6);
}


/* Configure PWM TOP LEFT on Arduino Due digital pin 8 */
void PWMFrontLeftConfigure(void)
{
	/* Initiate and configure PWM TOP LEFT */
	PWMTopLeftChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMTopLeftChannelInstance.polarity = PWM_POLARITY;
	PWMTopLeftChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMTopLeftChannelInstance.ul_period = 1000;
	PWMTopLeftChannelInstance.ul_duty = 0;
	PWMTopLeftChannelInstance.channel = PWM_CHANNEL_5;
	pwm_channel_init(PWM,&PWMTopLeftChannelInstance);
	
	/* Configure PWM TOP LEFT output pin*/
	pio_set_peripheral(PWMTOPLEFTPIO, PWMTOPLEFTPERIPHERAL, PWMTOPLEFTPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_5);
}


/* Configure PWM TOP RIGHT on Arduino Due digital pin 6 */
void PWMFrontRightConfigure(void)
{
	/* Initiate and configure PWM TOP RIGHT */
	PWMTopRightChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMTopRightChannelInstance.polarity = PWM_POLARITY;
	PWMTopRightChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMTopRightChannelInstance.ul_period = 1000;
	PWMTopRightChannelInstance.ul_duty = 0;
	PWMTopRightChannelInstance.channel = PWM_CHANNEL_7;
	pwm_channel_init(PWM,&PWMTopRightChannelInstance);
	
	/* Configure PWM TOP RIGHT output pin*/
	pio_set_peripheral(PWMTOPRIGHTPIO, PWMTOPRIGHTPERIPHERAL, PWMTOPRIGHTPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_7);
}


/* Configure PWM LOWER LEFT on Arduino Due digital pin 38 */
void PWMBackLeftConfigure(void)
{
	/* Initiate and configure PWM LOWER LEFT */
	PWMLowerLeftChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMLowerLeftChannelInstance.polarity = PWM_POLARITY;
	PWMLowerLeftChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMLowerLeftChannelInstance.ul_period = 1000;
	PWMLowerLeftChannelInstance.ul_duty = 0;
	PWMLowerLeftChannelInstance.channel = PWM_CHANNEL_2;
	pwm_channel_init(PWM,&PWMLowerLeftChannelInstance);
	
	/* Configure PWM LOWER LEFT output pin*/
	pio_set_peripheral(PWMLOWERLEFTPIO, PWMLOWERLEFTPERIPHERAL, PWMLOWERLEFTPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_2);
}


/* Configure PWM LOWER RIGHT on Arduino Due digital pin 9 */
void PWMBackRightConfigure(void)
{
	/* Initiate and configure PWM LOWER RIGHT */
	PWMLowerRightChannelInstance.alignment = PWM_ALIGN_LEFT;
	PWMLowerRightChannelInstance.polarity = PWM_POLARITY;
	PWMLowerRightChannelInstance.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWMLowerRightChannelInstance.ul_period = 1000;
	PWMLowerRightChannelInstance.ul_duty = 0;
	PWMLowerRightChannelInstance.channel = PWM_CHANNEL_4;
	pwm_channel_init(PWM,&PWMLowerRightChannelInstance);
	
	/* Configure PWM LOWER RIGHT output pin*/
	pio_set_peripheral(PWMLOWERRIGHTPIO, PWMLOWERRIGHTPERIPHERAL, PWMLOWERRIGHTPIN);
	pwm_channel_enable(PWM,PWM_CHANNEL_4); 
}


/* Function that changes duty cycle for front fans */
void PWMSetDutyCycleFront(uint32_t DutyCycleTopRight, uint32_t DutyCycleTopLeft){

	pwm_channel_update_duty(PWM,&PWMTopRightChannelInstance,DutyCycleTopRight);
	pwm_channel_update_duty(PWM,&PWMTopLeftChannelInstance,DutyCycleTopLeft);
}


/* Function that changes duty cycle for back fans */
void PWMSetDutyCycleBack(uint32_t DutyCycleLowerRight, uint32_t DutyCycleLowerLeft){
	
	pwm_channel_update_duty(PWM,&PWMLowerRightChannelInstance,DutyCycleLowerRight);
	pwm_channel_update_duty(PWM,&PWMLowerLeftChannelInstance,DutyCycleLowerLeft);
}
