;******************************************************************
; Materia......: Laboratorio de Microprocesadores.
; Curso........: Campigglio - Stola
; Fecha inicio.: 14/03/2016
; Fecha entrega: 21/06/2016
; Autores......:
;		 Ezequiel Martín Zarza
;		 Santiago Roman
;		 Federico Verstraeten
;
; Contacto.....:
;		 ezequielm.zarza@gmail.com
;		 santiago_roman@outlook.com
;		 federico.verstraeten@gmail.com
;
;******************************************************************
;       MAIN
;******************************************************************
; Programa principal
;******************************************************************


;******************************************************************
; Includes
;******************************************************************

	.include "asminc/m32def.inc"
	.include "asminc/menu_def.inc"
	.include "asminc/register_alias.inc"
	.include "asminc/macros.inc"

;******************************************************************
; Memorias definiciones.
;******************************************************************

; Segmento EEPROM
.eseg
.org 0x0000

; Segmento Datos en SRAM
.dseg
	var:	.byte	6
        buffer: .byte   5

; Segmento Codigo en Flash-ROM
.cseg
.org 0x0000
	rjmp 	RESET
.org INT0addr
        rjmp    press_interrupt


;*****************************************************************
; Inicialización del micro luego del RESET. Iniciar Stack-Pointer
;*****************************************************************

RESET:
	ldi	tmp, low(RAMEND)
	out	SPL, tmp
	ldi	tmp, high(RAMEND)
	out	SPH, tmp
        rjmp    MAIN

;*****************************************************************
; MAIN. Rutina principal del microcontrolador.
;*****************************************************************

MAIN:
        ; Inicializamos las interrupciones
        rcall   interrupt_init

	; Inicializamos el display
	rcall	lcd_init

	; Inicializamos la comunicación serie
	rcall 	usart_init

        ; Inicializamos el DAC
        rcall   signal_init

        ; Inicializamos el ADC
        rcall   intensity_init

	; Inicializamos el menu
	rcall	menu_init

	; Mostramos el menu
	rcall   show_menu

        rjmp    EndProgram

; Codigo de jmps del menu
.include "asminc/menu_flow.inc"

; Codigo correspondiente a las diferentes rutinas del programa
.include "asminc/delay.inc"
.include "asminc/usart.inc"
.include "asminc/matlab.inc"
.include "asminc/signal.inc"
.include "asminc/bin_to_ascii.inc"
.include "asminc/intensity.inc"
.include "asminc/lcd.inc"
.include "asminc/interrupt.inc"
.include "asminc/menu.inc"

;*****************************************************************
; EndProgram: El programa nunca debería llegar hasta aca, pero
; si llega a pasar debido a un error se genera un loop infinito.
;*****************************************************************

EndProgram:
	rjmp    EndProgram

