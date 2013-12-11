#include <stdint.h>

#include <avr/io.h>
#include <util/delay_basic.h>
#define F_CPU 2000000UL
#include <util/delay.h>

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
	ECP.DIRSET = WE;


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
#warning "DO NOT USE eeprom_write_byte with a <5V AVR without proper protection!"
void eeprom_write_byte(uint16_t addr, uint8_t byte) {
	// Load address
	// 50ns address hold time
	EAPH_ADDR_OUT = addr >> 8;
	EAPL_ADDR_OUT = addr;

	// Load the data bus
	// 10ns data hold time
	EEPROM_DATA_OUT = byte;

	// Pull OE high
	EEPROM_OE(true);

	// OE pulled high in hardware
	// Pull WE low for a minimum of 100ns
	EEPROM_WE(false);
	// Delays roughly 256*3/F_CPU microseconds
	_delay_ms(1);
	_delay_loop_1(10);
	// May need to delay
	EEPROM_WE(true);


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
uint8_t eeprom_read_byte(uint16_t addr) {
	// Pull WE high to disable writing
	EEPROM_WE(true);

	// Set data port as inputs so the EEPROM can pull on the lines
	EDP.DIRCLR = PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm |
	             PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;

	// Point to the desired byte
	EAPH_ADDR_OUT = addr >> 8;
	EAPL_ADDR_OUT = addr;

	// Enable the output
	EEPROM_OE(false);


	return EEPROM_DATA_IN;
}
