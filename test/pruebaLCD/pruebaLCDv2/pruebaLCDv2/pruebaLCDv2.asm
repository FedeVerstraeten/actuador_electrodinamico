/*
 * pruebaLCDv2.asm
 *
 *  Created: 06/05/2016 12:04:26 p.m.
 *   Author: Eze
 */ 

 
; ---------------------------------------------------------LO QUE HICE YO-----------------------

.EQU LCD_DPRT = PORTD ; DATA PORT del LCD
.EQU LCD_DDDR = DDRD  ; DATA DDR del LCD
.EQU LCD_DPIN = PIND  ; DATA PIN del LCD
.EQU LCD_CPRT = PORTB ; COMANDS PORT LCD
.EQU LCD_CDDR = DDRB ;  COMANDS DDR LCD
.EQU LCD_CPIN = PINB ;  COMANDS PIN LCD del LCD
.EQU LCD_RS = 0		;LCD RS
.EQU LCD_RW = 1		;LCD RW
.EQU LCD_EN = 2		;LCD EN


			LDI R21,HIGH(RAMEND)
			OUT SPH,R21
			LDI R21,LOW(RAMEND)
			OUT SPL,R21

			LDI R21, 0xFF;
			OUT LCD_DDDR, R21	;LCD DATA PORT ES OUTPUT
			OUT LCD_CDDR, R21	;LCD COMMAND PORT ES OUTPUT
			CBI LCD_CPRT,LCD_EN	;LCD_EN=0
			CALL DELAY_2ms		;espera para encender
			LDI R16,0x38		;inicializo las dos lineas del LCD
			CALL CMNDWRT		;LLAMA A COMMAND FUNCTION
			CALL DELAY_2ms		;ESPERA 2MS
			LDI R16,0x0E		;DISPLAY ON, CURSOR ON
			CALL CMNDWRT		;CALL COMMAND FUNCTION
			LDI R16,0X01		;CLEAR LCD 
			CALL CMNDWRT		;
			CALL DELAY_2ms		;
			LDI R16,0x06		;
			CALL DELAY_2ms		;
			LDI R16,'H'			;
			CALL DATAWRT		;
			LDI R16,'I'			;
			CALL DATAWRT		;
HERE: JMP HERE
;----------------------------------------------------------------------------------------------------
CMNDWRT:
			OUT	LCD_DPRT,R16	;LCD DATA PORT = R16
			CBI LCD_CPRT,LCD_RS	;RS=0 PARA COMANDO
			CBI	LCD_CPRT,LCD_RW	;RW=0 PARA ESCRIBIR
			SBI LCD_CPRT,LCD_EN	;EN=1
			CALL SDELAY
			CBI LCD_CPRT,LCD_EN	;
			CALL DELAY_100us
			RET
;----------------------------------------------------------------------------------------------------
DATAWRT:
			OUT LCD_DPRT,R16	;LCD DATA PORT=R16
			SBI LCD_CPRT,LCD_RS	;RS=1 PARA DATO
			CBI LCD_CPRT,LCD_RW	;
			SBI LCD_CPRT,LCD_EN	;
			CALL SDELAY
			CBI LCD_CPRT,LCD_EN
			CALL DELAY_100us	;
			RET
;-----------------------------------------------------------------------------------------------------

SDELAY:
			NOP
			NOP
			RET
;-----------------------------------------------------------------------------------------------------

DELAY_100us:
			PUSH R17
			LDI R17,60
DR0:		
			CALL SDELAY
			DEC R17
			BRNE DR0
			POP R17
			RET
;------------------------------------------------------------------------------------------------------

DELAY_2ms:
			PUSH R17
			LDI R17,20
LDRO:		
			CALL DELAY_100us
			DEC	R17
			BRNE LDRO
			POP R17
			RET

