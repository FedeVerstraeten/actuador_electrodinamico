;******************************************************************
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
;******************************************************************
;	MACROS
;******************************************************************


;******************************************************************
;	MoveZTo: Mueve el puntero Z hasta la posición indicada.
;	ZH:ZL <- ZH:ZL + @0
;******************************************************************
	.MACRO	MoveZTo
		adiw	ZH:ZL,@0
	.ENDMACRO
;******************************************************************
;	LoadWord: Carga contenido en ROM apuntado por Z en registros
;	para Word (wrdh:wrdl). La dirección que almacenada en los 
;	registros se carga nuevamente en Z.
;	Z queda apuntando a una nueva dirección de memoria en ROM.
;
;	wrdh:wrdl <- (ZH:ZL)
;	ZH:ZL	<- wrdh:wrdl
;******************************************************************
	.MACRO	LoadWord
		lpm		wrdh,Z+
		lpm		wrdl,Z+
		movw	Zh:Zl,wrdh:wrdl
	.ENDMACRO

	.MACRO	SetLcdClearAtHome
;		ldi		arg,lcdclear
;		rcall	lcd_cmd4b
;		rcall	LCD_wait
;		ldi		arg,lcdhome
;		rcall	lcd_cmd4b
;		rcall	LCD_wait
	.ENDMACRO

	.MACRO	Secondline
		ldi		arg,sline
		rcall	LCD_cmd4b
		rcall	LCD_wait
	.ENDMACRO
