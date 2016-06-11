;
; signalRampa.asm
;
; Created: 31/05/2016 01:26:57 a.m.
;  Author: Eze 
;

.INCLUDE "M328PDEF.INC" 

 LDI R16, 0xFF
 OUT DDRB, R16; Hago que el puerto B sea de salida

 LOOP:
	INC R16			;Incremento R16
	OUT PORTB, R16	;Mando R16 al puerto B
	NOP				;Para que se "recupere" el DAC
	NOP
	RJMP LOOP