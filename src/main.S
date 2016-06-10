;******************************************************************
; Materia......: Laboratorio de Microprocesadores.
; Curso........: Campigglio - Stola
; Fecha inicio.: 14/03/2016
; Fecha entrega: 20/06/2016
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
;	MAIN
;******************************************************************
;	Programa principal
;******************************************************************


;******************************************************************
; Includes
;******************************************************************

	.include "asminc/m328Pdef.inc"
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

	; Segmento Codigo en Flash-ROM
	.cseg
	.org 0x0000
		rjmp 	RESET


;*****************************************************************
; Inicialización del micro luego del RESET. Iniciar Stack-Pointer
;*****************************************************************
RESET:
	ldi	tmp, low(RAMEND)
	out	SPL, tmp
	ldi	tmp, high(RAMEND)
	out	SPH, tmp
	;rjmp 	MAIN


;*****************************************************************
; MAIN. Rutina principal del microcontrolador.
;*****************************************************************
MAIN:
	; Inicializamos el display
	rcall	lcd_init

	; Inicializamos la comunicación serie
	rcall 	usart_init

	; Inicializamos el menu
	rcall	menu_init

	; Llamada display
	rcall   show_screen

	; Codigo de jmps del menu
	.include "asminc/menu_flow.inc"

	;; .include "asminc/common.inc"
	;; .include "asminc/ascii.inc"
	;; .include "asminc/spi_master.inc"
	.include "asminc/usart.inc"
	.include "asminc/lcd_driver.inc"
	.include "asminc/menu.inc"

EndProgram:
	rjmp    EndProgram

