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
;	MACROS
;******************************************************************


;******************************************************************
; MoveZTo: Mueve el puntero Z hasta la posición indicada.
; ZH:ZL <- ZH:ZL + @0. Usado para desplazarse en las cadenas (.db)
; que forman al menu.
;******************************************************************
.MACRO	MoveZTo
	adiw	ZH:ZL, @0
.ENDMACRO


;******************************************************************
; LoadWord: Carga contenido en ROM apuntado por Z en registros
; para Word (wrdh:wrdl). La dirección que almacenada en los
; registros se carga nuevamente en Z.
; Z queda apuntando a una nueva dirección de memoria en ROM.
; wrdh:wrdl <- (ZH:ZL)
; ZH:ZL	<- wrdh:wrdl
;******************************************************************
.MACRO	LoadWord
	lpm	wrdh, Z+
	lpm	wrdl, Z+
	movw	Zh:Zl, wrdh:wrdl
.ENDMACRO

;******************************************************************
; SetLCDClearAtHome: Limpia la pantalla del display y luego ubica
; al cursor en Home.
;******************************************************************

.MACRO	SetLcdClearAtHome
	ldi	arg, LCD_CLEAR
	rcall	lcd_send_cmd_4b
	rcall	lcd_wait
	ldi	arg, LCD_CURSOR_HOME
	rcall	lcd_send_cmd_4b
	rcall	lcd_wait
.ENDMACRO

;******************************************************************
; SecondLine: Ubica al cursor en el inicio de la segunda
; línea del display.
;******************************************************************

.MACRO	SecondLine
	ldi	arg, LCD_CURSOR_2LINE
	rcall	lcd_send_cmd_4b
	rcall	lcd_wait
.ENDMACRO
