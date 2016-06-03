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
;	MENU
;******************************************************************
;	Rutinas utilizadas para el funcionamiento del menu.
;******************************************************************

MENU_init:
;		;*inicializo Flags
;		ldi 	Yh,0x00
;		ldi 	Yl,0x01
;		ldi tmp,1
		; Posición inicial del menu
		ldi		Xh,high(Matlab<<1)
		ldi		Xl,low(Matlab<<1)
;		;seteo los SWITCHes como entrada con pull up on
;		cbi		DDRC,SWITCHUP
;		cbi		DDRC,SWITCHDW
;		cbi		DDRC,SWITCHRT
;		sbi		PORTC,SWITCHUP
;		sbi		PORTC,SWITCHDW
;		sbi		PORTC,SWITCHRT
;		;cargo mi registro ZERO
;		clr		zero
;		ret
