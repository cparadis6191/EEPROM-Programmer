CC=avr-gcc
CFLAGS=-Os -std=c99 -Wall -Wextra -mmcu=atxmega128a4u
OBJ2HEX=avr-objcopy
ADFLAGS=-p x128a4 -c dragon_isp -P usb

TARGET=EEPROM-Programmer
OBJS=eeprom.o


all: ${TARGET}
${TARGET}: ${OBJS}
eeprom.o: eeprom.h


flash:
	avrdude ${ADFLAGS}


clean:
	rm -rf ${TARGET} ${OBJS}
