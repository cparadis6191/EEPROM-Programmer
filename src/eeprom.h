#ifndef __EEPROM_H_
#define __EEPROM_H_

#define HIGH 1
#define LOW  0

// EEPROM Data lines on PORTC
#define EDP PORTC
#define EEPROM_DATA_OUT EDP.OUT
#define EEPROM_DATA_IN EDP.IN

// EEPROM Address lines on PORTA and PORTB
#define EAPL PORTA
#define EAPH PORTB
#define EEPROM_ADDR(ADDR) EAPL.OUT = ADDR, EAPH.OUT = (ADDR >> 8)

// All control lines are on PORTD
#define ECP PORTD
#define CE0 PIN0_bm
#define WE0 PIN1_bm
#define CE1 PIN2_bm
#define WE1 PIN3_bm
#define CE2 PIN4_bm
#define WE2 PIN5_bm

#define EEPROM0_CE(VAL) if (VAL) { ECP.OUTCLR = CE0; \
						} else { ECP.OUTSET = CE0; }
#define EEPROM0_WE(VAL) if (VAL) { ECP.OUTCLR = WE0; \
						} else { ECP.OUTSET = WE0; }

#define EEPROM1_CE(VAL) if (VAL) { ECP.OUTCLR = CE1; \
						} else { ECP.OUTSET = CE1; }
#define EEPROM1_WE(VAL) if (VAL) { ECP.OUTCLR = WE1; \
						} else { ECP.OUTSET = WE1; }

#define EEPROM2_CE(VAL) if (VAL) { ECP.OUTCLR = CE2; \
						} else { ECP.OUTSET = PICE2; }
#define EEPROM2_WE(VAL) if (VAL) { ECP.OUTCLR = WE2; \
						} else { ECP.OUTSET = WE2; }

// Maybe don't need these
// Might just tie them low
/*#define OE1 PIN0_bm
#define OE0 PIN0_bm
#define OE2 PIN0_bm
#define EEPROM2_OE(VAL) if (VAL) { ECP.OUTCLR = PIN8_bm; \
						} else { ECP.OUTSET = PIN8_bm; }
#define EEPROM1_OE(VAL) if (VAL) { ECP.OUTCLR = PIN5_bm; \
						} else { ECP.OUTSET = PIN5_bm; }
#define EEPROM0_OE(VAL) if (VAL) { ECP.OUTCLR = PIN2_bm; \
						} else { ECP.OUTSET = PIN2_bm; }*/

void eeprom_init(void);

void eeprom_write_byte(uint16_t addr, char byte);
char eeprom_read_byte(uint16_t addr);


#endif
