#ifndef __IO_H_
#define __IO_H_

#include <stdbool.h>

#define F_CPU 2000000UL
#include <util/delay.h>


// Button is 3.3V when pressed
#define BTNPORT PORTR
#define BTNCTRL BTNPORT.PIN1CTRL
#define BTNPIN PIN1_bm
#define BUTTON (BTNPORT.IN & BTNPIN)

// LED
// Pull pin low to turn on
#define LEDPORT PORTR
#define LEDPIN PIN0_bm
#define LED(VAL) if (VAL) { LEDPORT.OUTCLR = LEDPIN; \
                 } else     LEDPORT.OUTSET = LEDPIN
#define LED_TGL() LEDPORT.OUTTGL = LEDPIN

void io_init(void);

void wait_for_press(void);


#endif