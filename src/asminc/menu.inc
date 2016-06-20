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
;       MENU
;******************************************************************
; Rutinas utilizadas para el funcionamiento del menu.
;******************************************************************

menu_init:
	; Posición inicial del menu
	ldi	Xh, high(Matlab<<1)
	ldi	Xl, low(Matlab<<1)
	; Seteo los switches como entrada con pull-up on
	cbi	MENU_DDR, SWITCHUP
	cbi	MENU_DDR, SWITCHDW
	cbi	MENU_DDR, SWITCHEN
	sbi	MENU_PORT, SWITCHUP
	sbi	MENU_PORT, SWITCHDW
	sbi	MENU_PORT, SWITCHEN
	ret

;*****************************************************************
; lcd_putstring: Va leyendo caracteres a los que apunta Z
; hasta que llega al valor ENDSTR, el cual indica el fin de la
; cadena de caracteres a mostrar.
;*****************************************************************

lcd_putstring:
	lpm	arg, Z+
putstring_loop:
	LcdPutchar
	lpm	arg, Z+
	cpi     arg, ENDSTR
	brne    putstring_loop
	ret
