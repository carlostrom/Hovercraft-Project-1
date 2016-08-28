/*
* ADFunctions.c
*
* This file contains functions that creates and initiates ADC´s on different
* analog input pins on the Arduino Due-board.
*
*  Authors: Karl Mösenbacher & Carl Öström
*/


#include "asf.h"
#include "ADFunctions.h"
uint32_t topright;
uint32_t topleft;


/* Initiate AD-converter on Arduino Due Analog pins */
void ADCConfigure(void)
{
	pmc_enable_periph_clk(ID_ADC);
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_10);
	
	adc_enable_channel(ADC, TOPLEFT_CHANNEL); /* Initiate AD-converter on Arduino Due Analog pin  A0 */
	adc_enable_channel(ADC, TOPRIGHT_CHANNEL); /* Initiate AD-converter on Arduino Due Analog pin  A1 */
	adc_enable_channel(ADC, LOWLEFT_CHANNEL); /* Initiate AD-converter on Arduino Due Analog pin  A2 */
	adc_enable_channel(ADC, LOWRIGHT_CHANNEL); /* Initiate AD-converter on Arduino Due Analog pin  A3 */
	
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}


/* Reads and returns the incoming value from Arduino Due analog pin A0 */
uint32_t ReadTopLeft(void)
{
	adc_start(ADC);
	
	/* Read ADC value from channel 7 */
	if(adc_get_channel_status(ADC, TOPLEFT_CHANNEL))
	{
		return adc_get_channel_value(ADC, TOPLEFT_CHANNEL)* 1.3;
		} else {
		return 0;
	}
}


/* Reads and returns the incoming value from Arduino Due analog pin A1 */
uint32_t ReadTopRight(void)
{
	adc_start(ADC);
	
	/* Read ADC value from channel 6 */
	if(adc_get_channel_status(ADC, TOPRIGHT_CHANNEL))
	{
		return adc_get_channel_value(ADC, TOPRIGHT_CHANNEL) * 1.3;
		} else {
		return 0;
	}
}


/* Reads and returns the incoming value from Arduino Due analog pin A2 */
uint32_t ReadLowerLeft(void)
{
	adc_start(ADC);
	
	/* Read ADC value from channel 5 */
	if(adc_get_channel_status(ADC, LOWLEFT_CHANNEL))
	{
		return adc_get_channel_value(ADC, LOWLEFT_CHANNEL)* 1.3;
		} else {
		return 0;
	}
}


/* Reads and returns the incoming value from Arduino Due analog pin A3 */
uint32_t ReadLowerRight(void)
{
	adc_start(ADC);
	
	/* Read ADC value from channel 4 */
	if(adc_get_channel_status(ADC, LOWRIGHT_CHANNEL))
	{
		return adc_get_channel_value(ADC, LOWRIGHT_CHANNEL)* 1.3;
		} else {
		return 0;
	}
}
