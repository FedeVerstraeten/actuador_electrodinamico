# Nombre del proyecto
PROJECT = actuador

# Microcontrolador que se utiliza
MICRO = m32

# Ensamblador a utilizar
ASMBLER = avra
ASMBLERARGS = -o "$(PROJECT)"

# Archivos de codigo
MASTER = main.S
INCDIR = asminc
INC := $(wildcard $(INCDIR/*.inc))

# Archivos ensamblados
BUILDDIR = build

all: master

master: $(MASTER) $(INC)
	$(ASMBLER) $(MASTER) $(ASMBLERARGS)
	mv *.hex $(BUILDDIR)/
	mv *.cof $(BUILDDIR)/
	mv *.obj $(BUILDDIR)/

clean:
	rm *.hex *.cof *.HEX *.LST *.obj *.SDI

clean_win:
	rm \*.hex \*.cof \*.HEX \*.LST \*.obj \*.SDI

program:
	avrdude -c usbtiny -p $(MICRO) -U flash:w:build/main.S.hex

hfuse:
	avrdude -c usbtiny -p $(MICRO) -U hfuse:w:0xD7:m

lfuse:
	avrdude -c usbtiny -p $(MICRO) -U lfuse:w:0xC7:m
