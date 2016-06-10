# Nombre del proyecto
PROJECT = actuador

# Microcontrolador que se utiliza
MICRO = m328p

# Ensamblador a utilizar
ASMBLER = avra
ASMBLERARGS = -o "$(PROJECT)"

all: master

master: master.asm
	$(ASMBLER) master.asm $(ASMBLERARGS)

clean:
	rm *.hex *.cof *.HEX *.LST *.obj *.SDI

clean_win:
	rm \*.hex \*.cof \*.HEX \*.LST \*.obj \*.SDI

program:
	avrdude -c usbtiny -p $(MICRO) -U flash:w:$(PROJECT).hex

hfuse:
	avrdude -c usbtiny -p $(MICRO) -U hfuse:w:0xD7:m

lfuse:
	avrdude -c usbtiny -p $(MICRO) -U lfuse:w:0xC7:m
