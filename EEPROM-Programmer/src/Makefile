CC=avr-gcc
CFLAGS=-Os -std=c99 -Wall -Wextra -mmcu=atxmega16a4u
OBJ2HEX=avr-objcopy
AVRDUDE=avrdude
ADFLAGS=-p x16a4 -c dragon_pdi -P usb

TARGET=EEPROM-Programmer
OBJS=${TARGET}.o eeprom.o io.o
.PHONY: flash erase clean


all: ${TARGET}.obj


${TARGET}.obj: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${TARGET}.obj

eeprom.o: eeprom.h
io.o: io.h
${TARGET}.obj: ${OBJS}



flash: ${TARGET}.hex ${TARGET}.eeprom
	${AVRDUDE} ${ADFLAGS} -V -U flash:w:${TARGET}.hex:i

%.obj: %.o
	${CC} ${CFLAGS} $< -o $@

%.hex: %.obj
	${OBJ2HEX} -R .eeprom -O ihex $< $@

%.eeprom: %.obj
	${OBJ2HEX} -j .eeprom -O ihex $< $@


erase:
	${AVRDUDE} ${ADFLAGS} -E noreset -e

clean:
	rm -f ${TARGET} ${OBJS} ${TARGET}.obj ${TARGET}.hex ${TARGET}.eeprom
