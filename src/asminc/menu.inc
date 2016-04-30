;------------------------------------------------------------------
; Materia......: Laboratorio de Microcomputadoras.
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
;------------------------------------------------------------------
;	MENU
;------------------------------------------------------------------
;	Rutinas utilizadas para el funcionamiento del menu.
;------------------------------------------------------------------

MENU_init:
;		;*inicializo Flags
;		ldi 	Yh,0x00
;		ldi 	Yl,0x01
;		ldi tmp,1
;		;seteo posición inicial del menu
;		ldi		Xh,high(Lectura<<1)
;		ldi		Xl,low(Lectura<<1)
;		;seteo los switches como entrada con pull up on
;		cbi		DDRC,switchUP
;		cbi		DDRC,switchDW
;		cbi		DDRC,switchRT
;		sbi		PORTC,switchUP
;		sbi		PORTC,switchDW
;		sbi		PORTC,switchRT
;		;seteo pin lampara como salida en 0
;		sbi		DDRC,lamp
;		cbi		PORTC,lamp
;		;cargo mi registro ZERO
;		clr		zero
;		ret
