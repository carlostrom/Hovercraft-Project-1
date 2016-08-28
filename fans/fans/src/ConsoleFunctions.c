/*
* ConsoleFunctions.c
*
* This file contains functions that makes it possible to print
* data or information in Atmel`s terminal window
*
* Authors: Karl Mösenbacher & Carl Öström
*/


#include "asf.h"
#include "ConsoleFunctions.h"


/* Configure Atmel´s console window */
void ConfigureConsole(void)
{
	const usart_serial_options_t uart_serial_options = { .baudrate = CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	ioport_set_pin_mode(PIO_PA8_IDX, IOPORT_MODE_PULLUP);
	
	/* Make sure that stdout doesnt  buffering */
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	#endif
}