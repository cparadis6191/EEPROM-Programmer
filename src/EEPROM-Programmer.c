#include <avr/io.h>
#include <stdlib.h>


#include "EEPROM-Programmer.h"
#include "eeprom.h"


int main(void) {
	uint32_t prog[255] = {};
	size_t f_size;

	eeprom_init();


	while (1) {
		// Read in file
		// Use either UART or USB

		// Find file length
		f_size = sizeof(prog);


		for (uint16_t i = 0; i < 255; i++) {
			eeprom_write_word(i, prog[i]);
		}
	}


	return 0;
}
