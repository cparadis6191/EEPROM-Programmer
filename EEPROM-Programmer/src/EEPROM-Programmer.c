#include <stdlib.h>
#include <stdbool.h>

#include <avr/io.h>

#include "EEPROM-Programmer.h"
#include "eeprom.h"
#include "data.h"
#include "io.h"


int main(void) {
	size_t f_size;
	uint8_t byte;

	io_init();
	eeprom_init();


	// data defined in data.h
	// data resides in program space instead of main memory
	f_size = sizeof(data);

	wait_for_press();
	for (size_t i = 0; i < f_size; i++) {
		// Read the byte in from program space
		byte = pgm_read_byte(&(data[0]));

		eeprom_write_word(i, byte);
	}
	while (1) {}


	return 0;
}
