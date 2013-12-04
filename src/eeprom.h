#ifndef __EEPROM_H_
#define __EEPROM_H_


#define HIGH 1
#define LOW  0

// EEPROM Data lines on PORTC
#define EDP PORTD
#define EEPROM_DATA_OUT EDP.OUT
#define EEPROM_DATA_IN EDP.IN

// EEPROM Address lines on PORTB and PORTA
// ADDR[10..0] is mapped to PORTB[10..8] and PORTA[7..0]
#define EAPH PORTB
#define EAPL PORTA
#define EEPROM_ADDR(ADDR) EAPH.OUT = ADDR >> 8; \
                          EAPL.OUT = ADDR

// All control lines are on PORTD
#define ECP PORTC
#define WE2 PIN2_bm
#define WE1 PIN1_bm
#define WE0 PIN0_bm

// Note that EEPROM has .8V and 2.0V logic thresholds
#define EEPROM2_WE(VAL) if (VAL) { ECP.OUTCLR = WE2; \
                        } else     ECP.OUTSET = WE2

#define EEPROM1_WE(VAL) if (VAL) { ECP.OUTCLR = WE1; \
                        } else     ECP.OUTSET = WE1

#define EEPROM0_WE(VAL) if (VAL) { ECP.OUTCLR = WE0; \
                        } else     ECP.OUTSET = WE0


void eeprom_init(void);

void eeprom_write_word(uint16_t addr, uint32_t word);
uint32_t eeprom_read_word(uint16_t addr);


#endif
