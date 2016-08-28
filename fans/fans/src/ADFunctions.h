/*
 * ADFunctions.h
 *
 *  Authors: Karl Mösenbacher & Carl Öström
 */ 


#ifndef ADFUNCTIONS_H_
#define ADFUNCTIONS_H_


/* AD-converter Channels */
#define TOPLEFT_CHANNEL ADC_CHANNEL_7
#define TOPRIGHT_CHANNEL ADC_CHANNEL_6
#define LOWLEFT_CHANNEL ADC_CHANNEL_5
#define LOWRIGHT_CHANNEL ADC_CHANNEL_4


/* Functions for ADC`s */
void ADCConfigure(void);
uint32_t ReadFrontRight(void);
uint32_t ReadFrontLeft(void);
uint32_t ReadBackRight(void);
uint32_t ReadBackLeft(void);


#endif /* ADFUNCTIONS_H_ */