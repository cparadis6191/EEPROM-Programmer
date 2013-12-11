#ifndef __EEPROM_H_
#define __EEPROM_H_

#include <stdbool.h>


// EEPROM Data lines on PORTC
#define EDP PORTC
#define EEPROM_DATA_OUT EDP.OUT
#define EEPROM_DATA_IN EDP.IN

// EEPROM Address lines on PORTB and PORTA
// ADDR[10..0] is mapped to PORTB[10..8] and PORTA[7..0]
#define EAPH PORTB
#define EAPL PORTA
#define EAPH_ADDR_OUT EAPH.OUT
#define EAPL_ADDR_OUT EAPL.OUT

// All control lines are on PORTD
#define ECP PORTD
#define WE PIN1_bm
#define OE PIN0_bm

// Note that EEPROM has .8V and 2.0V logic thresholds
// Use the chip's active low logic
// false is enabled, true is disabled
#define EEPROM_WE(VAL) if (VAL) { ECP.OUTSET = WE; \
                       } else     ECP.OUTCLR = WE
#define EEPROM_OE(VAL) if (VAL) { ECP.OUTSET = OE; \
                       } else     ECP.OUTCLR = OE

void eeprom_init(void);

void eeprom_write_byte(uint16_t addr, uint8_t byte);
uint8_t eeprom_read_byte(uint16_t addr);


#endif
