#include <stdlib.h>

#include <avr/io.h>

#include "EEPROM-Programmer.h"
#include "eeprom.h"
#include "data.h"
#include "io.h"


int main(void) {
	size_t d_size;
	uint8_t byte;

	io_init();
	eeprom_init();


	// data defined in data.h
	// data resides in program space instead of main memory
	d_size = sizeof(data);

	LED(true);
	wait_for_press();
	for (uint16_t addr = 0; addr < d_size; addr++) {
		// Read the byte in from program space
		byte = pgm_read_byte(&(data[addr]));

		// Write to external EEPROm
		eeprom_write_byte(addr, byte);
	}

	// Read the data out by byte
	for (uint16_t addr = 0; addr; addr++) {
		eeprom_read_byte(addr);

		LED_TGL();
		wait_for_press();
	}
	while (1) {}


	return 0;
}
