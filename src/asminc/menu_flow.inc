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
; showScreen: Rutina principal de muestra por Display.
; Carga la primer linea y segunda línea en el Display, corriendo
; el puntero Z a la posición del Handler en la tabla de OPTIONS,
; y así ejecutando la sentencia correspondiente.
; (ver "Table Options" en archivo menu_def.inc).
;******************************************************************
showScreen:
		SetLcdClearAtHome
		movw	Zh:Zl,Xh:Xl
		MoveZTo (FIRSTLINEHANDLER)
		rcall	jumper
		movw	Zh:Zl,Xh:Xl
		MoveZTo (SECONDLINEHANDLER)
		rcall   jumper
		rjmp	checkButtons

;******************************************************************
; checkButtons: Rutina lectura de botón de entrada: UP, DOWN, ENTER
; Lee desde puerto donde se conectan, si el mismo ha sido presionado
; estará PINx.n=0 (cero) y se ejecuta rutina asociada. La rutina
; checkButtons repite hasta que sea presionado algún botón.
;******************************************************************
checkButtons:
		;reseteo las flags de las keys
		;rcall delay200ms

		;Lectura puerto C
		;Botón presionado el bit estará en cero
		in	tmp,PINC
		sbrs	tmp,SWITCHUP
		rjmp	pressUP
		sbrs	tmp,SWITCHDW
		rjmp	pressDOWN
		sbrs	tmp,SWITCHEN
		rjmp	pressEN
		;Se repite  mientras no se presione un botón
		;luego de esperar por posibles rebotes
		rjmp	checkButtons

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
; pressUp,pressDown,pressEnter: Desplazamiento puntero Z por tabla
; OPTIONS_TABLE tantas posiciones según el botón presionado.
;******************************************************************
pressUp:
		movw	Zh:Zl,Xh:Xl
		;MoveZTo	(PREV)
		rjmp	jumper

pressDown:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(NEXT)
		rjmp	jumper

pressEnter:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(ENTER)
		rjmp	jumper

;******************************************************************
; fstLineStrDisplay: First Line String Display '>'
; Desplaza el puntero Z por la tabla OPTIONS_TABLE, e imprime en la
; primer línea del Display el mensaje correspondiente, con el
; Cursor indicador al comienzo del String.
;
; sndLineStrDisplay: Second Line String Display ' '
; Desplaza el puntero Z por la tabla OPTIONS_TABLE, e imprime en la
; segunda línea del Display el mensaje correspondiente, con un
; espacio vacío al comienzo del String.
;
; endLineStrDisplay: End Line String Display ' '
; Puntero Z dezplazado por la tabla OPTIONS_TABLE a la última
; posición. Imprime en la primer línea del Display el mensaje
; correspondiente un espacio en blanco al comienzo del String.
;******************************************************************

fstLineStrDisplay:
		ldi	arg,'>'
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (FIRSTLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
		ret

sndLineStrDisplay:
		Secondline
		ldi	arg,' '
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (SECONDLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
		ret

endLineStrDisplay1:
		ldi	arg,' '
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (FIRSTLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring

endLineStrDisplay2:
		Secondline
		ldi	arg,'>'
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (SECONDLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
		ret

;******************************************************************
; Optionns Routines:
; Conjunto de subrutinas con prefijo "opt" de nombre. Corren el
; puntero X a la opción de la tabla OPTIONS_TABLE que corresponde.
; Luego de ello ejecutan la rutina showScreen.
; Estas son invocadas por las rutinas de interacción por con los
; botones u otras subrutinas.
;******************************************************************

optMatlab:
		ldi	Xh,high(Matlab<<1)
		ldi	Xl,low(Matlab<<1)
		rjmp 	showScreen

optSeno:
		ldi	Xh,high(Seno<<1)
		ldi	Xl,low(Seno<<1)
		rjmp	showScreen

optCuadrada:
		ldi	Xh,high(Cuadrada<<1)
		ldi	Xl,low(Cuadrada<<1)
		rjmp	showScreen

optSierra:
		ldi	Xh,high(Sierra<<1)
		ldi	Xl,low(Sierra<<1)
		rjmp	showScreen

optIntensidad:
		ldi	Xh,high(Intensidad<<1)
		ldi	Xl,low(Intensidad<<1)
		rjmp	showScreen

;******************************************************************
; commMatlab:
; Handler inicio comunicación con Matlab.
;******************************************************************
commMatlab:
;		SetLcdClearAtHome
;		ldi 	zh,high(strBusy<<1)
;		ldi 	zl,low(strBusy<<1)
;		rcall 	LCD_PutString
;		rcall 	StartReading
;		rcall 	SaveReading
;		clr 	yh
;		clr 	yl
;		ldi		Xh,high(Resultados<<1)
;		ldi		Xl,low(Resultados<<1)
		rjmp 	ShowScreen

;******************************************************************
; gen:
; Generación funciones precargadas.
;******************************************************************

genSeno:
		rjmp 	ShowScreen
genCuadrada:
		rjmp 	ShowScreen
genSierra:
		rjmp 	ShowScreen

medInten
		rjmp 	ShowScreen
