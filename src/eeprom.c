#include <avr/io.h>
#include <stdint.h>

#include "eeprom.h"


void eeprom_init(void) {
	// Set the address lines as outputs
	EAPL.DIRSET = PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm |
				  PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;
	EAPH.DIRSET = PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;

	// Set control lines as outputs
	ECP.DIRSET = CE0 | WE0 |
				 CE1 | WE1 |
				 CE2 | WE2;


	return;
}


/*
*	BYTE WRITE: Writing data into the AT28C16 is similar to
*	writing into a Static RAM. A low pulse on the WE or CE
*	input with OE high and CE or WE low (respectively) ini-
*	tiates a byte write. The address location is latched on the
*	last falling edge of WE (or CE); the new data is latched on
*	the first rising edge. Internally, the device performs a self-
*	clear before write. Once a byte write has been started, it
*	will automatically time itself to completion. Once a pro-
*	gramming operation has been initiated and for the duration
*	of t WC , a read operation will effectively be a polling operation.
*/
void eeprom_write_byte(uint16_t addr, char byte) {
	// Load address
	EEPROM_ADDR(addr);

	// Load the data bus
	EEPROM_DATA_IN = byte;

	// Pull OE high
	// Tied high in hardware

	// Pull WE low for 100ns to 1000ns
	EEPROM1_WE(LOW);
	// 50ns address hold time
	// 10ns data hold time

	// Should be fine to do nothing

	// Pull WE high
	EEPROM1_WE(HIGH);


	return;
}


/*
*	READ: The AT28C16 is accessed like a Static RAM.
*	When CE and OE are low and WE is high, the data stored
*	at the memory location determined by the address pins is
*	asserted on the outputs. The outputs are put in a high
*	impedance state whenever CE or OE is high. This dual line
*	control gives designers increased flexibility in preventing
*	bus contention.
*/
char eeprom_read_byte(uint16_t addr) {
	char byte;


	return byte;
}
