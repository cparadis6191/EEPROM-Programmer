#include <avr/io.h>

#include "io.h"


void io_init(void) {
	// Set the button as an input with a pulldown resistor
	BTNPORT.DIRCLR = BTNPIN;
	BTNCTRL = PORT_OPC_PULLDOWN_gc;
	
	// Set the LED as an output
	LEDPORT.DIRSET = LEDPIN;
	

	return;
}


void wait_for_press(void) {
	// Wait until the button is released
	// to make sure it isn't bouncing from a previous press
	while (BUTTON) {}
	_delay_ms(100);

	// Wait until the button is pressed and delay for 100ms
	while (!BUTTON) {}
	_delay_ms(100);

	
	return;
}