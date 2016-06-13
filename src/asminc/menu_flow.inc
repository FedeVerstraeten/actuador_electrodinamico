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
;	MENU_FLOW
;******************************************************************
; Implementación de rutinas y subrutinas ejecutadas en la
; interacción con el menú (ver definiciones en menu_def.inc).
;******************************************************************

;******************************************************************
; show_menu: Rutina principal de muestra por Display.
; Carga la primer línea y segunda línea en el Display, corriendo
; el puntero Z a la posición del Handler en la tabla de OPTIONS,
; y así ejecutando la sentencia correspondiente.
; (ver "Table Options" en archivo menu_def.inc).
;******************************************************************
show_menu:
	SetLcdClearAtHome
	movw	Zh:Zl, Xh:Xl
	MoveZTo (FSTLINEHANDLER)
	rcall	jumper
	movw	Zh:Zl, Xh:Xl
	MoveZTo (SNDLINEHANDLER)
	rcall   jumper
	rjmp	check_buttons

;******************************************************************
; check_buttons: Rutina lectura de botón de entrada: UP, DOWN, ENTER
; Lee desde puerto donde se conectan, si el mismo ha sido presionado
; estará PINx.n=0 (cero) y se ejecuta rutina asociada. La rutina
; check_buttons repite hasta que sea presionado algún botón.
;******************************************************************
check_buttons:
	; Reseteo las flags de las keys
	rcall delay_200ms

	; Botón presionado el bit estará en cero
	in	tmp, MENU_PIN
	sbrs	tmp, SWITCHUP
	rjmp	press_up
	sbrs	tmp, SWITCHDW
	rjmp	press_down
	sbrs	tmp, SWITCHEN
	rjmp	press_enter
	; Se repite mientras no se presione un botón
	; luego de esperar por posibles rebotes
	rjmp	check_buttons

;******************************************************************
; jumper: Rutina salto indirecto.
; Se carga el contenido de lo apuntado en ROM por Z, en el mismo
; registro Z. Luego se aplica el salto indirecto por ijmp.
;
; Z <- (Z)
; PC <- Z(15:0)
; PC(15:0) <- Z(15:0)
; PC(21:16) <- 0
;******************************************************************
jumper:
	LoadWord
	ijmp

;******************************************************************
; press_up,press_down,press_enter: Desplazamiento puntero Z por tabla
; OPTIONS_TABLE tantas posiciones según el botón presionado.
;******************************************************************
press_up:
	movw	Zh:Zl, Xh:Xl
	;; MoveZTo	(PREV)
	rjmp	jumper

press_down:
	movw	Zh:Zl, Xh:Xl
	MoveZTo	(NEXT)
	rjmp	jumper

press_enter:
	movw	Zh:Zl, Xh:Xl
	MoveZTo	(ENTER)
	rjmp	jumper

press_interrupt:
        rjmp RESET

;******************************************************************
; fstline_dsp: First Line String Display '>'
; Desplaza el puntero Z por la tabla OPTIONS_TABLE, e imprime en la
; primer línea del Display el mensaje correspondiente, con el
; Cursor indicador al comienzo del String.
;
; sndline_dsp: Second Line String Display ' '
; Desplaza el puntero Z por la tabla OPTIONS_TABLE, e imprime en la
; segunda línea del Display el mensaje correspondiente, con un
; espacio vacío al comienzo del String.
;
; endline_dsp: End Line String Display ' '
; Puntero Z dezplazado por la tabla OPTIONS_TABLE a la última
; posición. Imprime en la primer línea del Display el mensaje
; correspondiente un espacio en blanco al comienzo del String.
;******************************************************************

fstline_dsp:
	ldi	arg, '>'
	rcall 	lcd_putchar
	movw	Zh:Zl, Xh:Xl
	MoveZTo (FSTLINESTR)
	LoadWord
	rcall	lcd_putstring
	ret

sndline_dsp:
	Secondline
	ldi	arg, ' '
	rcall 	lcd_putchar
	movw	Zh:Zl, Xh:Xl
	MoveZTo (SNDLINESTR)
	LoadWord
	rcall	lcd_putstring
	ret

endline_dsp1:
	ldi	arg, ' '
	rcall 	lcd_putchar
	movw	Zh:Zl, Xh:Xl
	MoveZTo (FSTLINESTR)
	LoadWord
	rcall	lcd_putstring

endline_dsp2:
	Secondline
	ldi	arg, '>'
	rcall 	lcd_putchar
	movw	Zh:Zl, Xh:Xl
	MoveZTo (SNDLINESTR)
	LoadWord
	rcall	lcd_putstring
	ret

;******************************************************************
; Options Routines:
; Conjunto de subrutinas con prefijo "opt" de nombre. Corren el
; puntero X a la opción de la tabla OPTIONS_TABLE que corresponde.
; Luego de ello ejecutan la rutina show_menu.
; Estas son invocadas por las rutinas de interacción por con los
; botones u otras subrutinas.
;******************************************************************

opt_matlab:
	ldi	Xh, high(Matlab<<1)
	ldi	Xl, low(Matlab<<1)
	rjmp 	show_menu

opt_sin:
	ldi	Xh, high(Sine<<1)
	ldi	Xl, low(Sine<<1)
	rjmp	show_menu

opt_square:
	ldi	Xh, high(Square<<1)
	ldi	Xl, low(Square<<1)
	rjmp	show_menu

opt_sawt:
	ldi	Xh, high(Sawtooth<<1)
	ldi	Xl, low(Sawtooth<<1)
	rjmp	show_menu

opt_intnsty:
	ldi	Xh, high(Intnsty<<1)
	ldi	Xl, low(Intnsty<<1)
	rjmp	show_menu

;******************************************************************
; comm_matlab:
; Handler inicio comunicación con Matlab.
;******************************************************************
;; comm_matlab:
	;; SetLcdClearAtHome
	;; ldi 	zh, high(strBusy<<1)
	;; ldi 	zl, low(strBusy<<1)
	;; rcall 	lcd_putstring
	;; rcall 	StartReading
	;; rcall 	SaveReading
	;; clr 	yh
	;; clr 	yl
	;; ldi		Xh, high(Resultados<<1)
	;; ldi		Xl, low(Resultados<<1)
	;; rjmp 	show_menu

;******************************************************************
; gen:
; Generación funciones precargadas.
;******************************************************************

gen_sin:
	rjmp 	show_menu
gen_square:
	rjmp 	show_menu
gen_sawt:
	rjmp 	show_menu

med_intnsty:
	rjmp 	show_menu
