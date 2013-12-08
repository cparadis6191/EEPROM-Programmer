#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <util/delay_basic.h>

#include "eeprom.h"


void eeprom_init(void) {
	// Set the address lines as outputs
	EAPH.DIRSET = PIN2_bm | PIN1_bm | PIN0_bm;
	EAPL.DIRSET = PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm |
	              PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;

	// Set the data lines as outputs
	EDP.DIRSET = PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm |
	             PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;

	// Set control lines as outputs
	ECP.DIRSET = WE2 | WE1 | WE0;


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
void eeprom_write_word(uint16_t addr, uint32_t word) {
	char byte_h, byte_m, byte_l;

	// Load address
	// 50ns address hold time
	EEPROM_ADDR(addr);

	// Construct each portion of the instruction word
	byte_h = word >> 16;
	byte_m = word >> 8;
	byte_l = word >> 0;


	// Load the data bus
	// 10ns data hold time
	EEPROM_DATA_IN = byte_h;
	// OE pulled high in hardware
	// Pull WE low for a minimum of 100ns
	EEPROM2_WE(false);
	// Delays roughly 256*3/F_CPU microseconds
	_delay_loop_1(1);
	// May need to delay
	EEPROM2_WE(true);

	EEPROM_DATA_IN = byte_m;
	EEPROM1_WE(false);
	_delay_loop_1(1);
	EEPROM1_WE(true);

	EEPROM_DATA_IN = byte_l;
	EEPROM0_WE(false);
	_delay_loop_1(1);
	EEPROM0_WE(true);


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
uint32_t eeprom_read_word(uint16_t addr) { return (char) addr; }
