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
;	Includes
;******************************************************************

	.include "asminc/m328Pdef.inc" ; Revisar sea acorde al uC elegido
	.include "asminc/menu_def.inc"
	.include "asminc/register_alias.inc"
	.include "asminc/macros.inc"

;******************************************************************
;	Memorias definiciones.
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
; Inicialización del Micro luego del RESET. Iniciar Stack-Pointer
;*****************************************************************
	RESET:
			ldi	tmp, low(RAMEND)
			out	SPL, tmp
			ldi	tmp, high(RAMEND)
			out	SPH, tmp
			;rjmp 	MAIN


;*****************************************************************
; MAIN. Rutina principal del micro controlador.
;*****************************************************************
	MAIN:

;		;seteo el prescaler para que divida por 4 la frec del cristal
;		ldi tmp,0x80
;		sts $0061,tmp
;		ldi tmp,0x02
;		sts $0061,tmp


;		;Habilitar LCD
;		rcall	LCD_init

;		;Iniciar el SPI como Master
;		rcall 	SPI_Minit

;		;Iniciar USART
;		rcall 	Usart_Init

;		;Config. inicial del Menu
		rcall	MENU_init

		;Llamada display
		rcall showScreen

;		;Codigo de jmps del menu.
	.include "asminc/menu_flow.inc"

;	.include "asminc/common.inc"
;	.include "asminc/ascii.inc"
;	.include "asminc/spi_master.inc"
;	.include "asminc/usart_master.inc"
;	.include "asminc/lcd_driver.inc"
	.include "asminc/menu.inc"

	EndProgram:
		rjmp EndProgram

