###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = 80C31
COMPILER = "ASEM-51 (Proteus)"
TARGET = Debug
SHELL = C:\Windows\system32\cmd.exe

## Tools general options

## Processing Tools
ASM=asem.exe
DDX=ASEMDDX.EXE
#  D:/Universidad/Laboratorio de Microprocesadores/simulacion rampa proteus/80C31/Debug/Debug/Debug.HEX: TOOL=ASM
#  Post: $(DDX) $(DDXFLAGS) Debug.lst
#     D:/Universidad/Laboratorio de Microprocesadores/pruebaRampa/signalRampa/signalRampa/signalRampa.asm

# Build tree:
all:	Debug

Debug:	Debug.HEX

Debug.HEX:	../../../../pruebaRampa/signalRampa/signalRampa/signalRampa.asm 
	$(ASM) "..\..\..\..\pruebaRampa\signalRampa\signalRampa\signalRampa.asm" "Debug.HEX" Debug.lst $(ASMFLAGS)  /INCLUDES:"C:\Program Files (x86)\Labcenter Electronics\Proteus 8 Professional\VSM Studio\Tools\ASEM51"
	$(DDX) $(DDXFLAGS) Debug.lst

# tidy - delete all temporary files which are not involved in the target generation
tidy:
	rm -rf Debug.lst

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.HEX
	rm -rf Debug.SDI

