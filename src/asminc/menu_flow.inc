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
;	MENU_FLOW
;******************************************************************
; Implementación rutinas y subrutinas ejectutadas en la interacción
; con el menú.
;******************************************************************

;******************************************************************
; showScreen: Rutina principal de muestra por Display.
; Carga la Primer linea y Segunda línea en el Display, corriendo
; el puntero Z a la posición del Handler en la tabla de OPTIONS,
; y así ejecutando la sentencia correspondiente.
; (ver "Table Options" en archivo menu_def.inc)
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
; check_keys: Rutina lectura de botón de entrada: UP, DOWN, ENTER
; Lee desde puerto donde se conectan, si el mismo ha sido presionado 
; estará PINx.n=0 (cero) y se ejecuta rutina asociada.
; La rutina check_keys repite hasta que sea presionado algún botón.
;******************************************************************
		
check_keys:
		;reseteo las flags de las keys
		rcall delay200ms
		;leo el puerto C
		in		tmp,PINC
		;si está presionado un boton va a quedar en 0 ese bit
		sbrs	tmp,switchUP
		rjmp	pressUP
		sbrs	tmp,switchDW
		rjmp	pressDOWN
		sbrs	tmp,switchEN
		rjmp	pressEN
		;si no se presiono nada me vuelvo a fijar
		;luego de esperar por posibles rebotes
		rjmp	check_keys

;******************************************************************
; jumper: Rutina salto indirecto. 
; Se carga el contenido de lo apuntado en ROM por Z en registro, en
; el mismo registro Z. Luego se aplica el salto indirecto por ijmp.
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
; PressUp,PressDown,PressEnter: Desplazamiento puntero Z por tabla
; OPTION TABLE tantas posiciones según el botón presionado.
;******************************************************************

PressUp:
		movw	Zh:Zl,Xh:Xl
		;MoveZTo	(PREV)
		rjmp	jumper
		
PressDown:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(NEXT)
		rjmp	jumper
		
PressEnter:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(ENTER)
		rjmp	jumper

;******************************************************************
; fstLineStrDisplay: First Line String Display '>'
; Desplaza el puntero Z por la tabla OPTION TABLE, e imprime en la
; primer línea del Display el mensaje correspondiente, con el 
; Cursor indicador al comienzo del String.
;
; sndLineStrDisplay: Second Line String Display ' '
; Desplaza el puntero Z por la tabla OPTION TABLE, e imprime en la
; segunda línea del Display el mensaje correspondiente, con un 
; espacio vacío al comienzo del String.
;
; endLineStrDisplay: End Line String Display ' '
; Puntero Z dezplazado por la tabla OPTION TABLE a la última
; posición. Imprime en la primer línea del Display el mensaje
; correspondiente un espacio en blanco al comienzo del String.
;******************************************************************
		
fstLineStrDisplay: 
		ldi		arg,'>'
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (FIRSTLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
		ret
		
sndLineStrDisplay:
		Secondline
		ldi		arg,' '
		rcall 	lcd_putc		
		movw	Zh:Zl,Xh:Xl
		MoveZTo (SECONDLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
		ret
		
endLineStrDisplay:
		ldi		arg,' '
		rcall 	lcd_putc
		movw	Zh:Zl,Xh:Xl
		MoveZTo (FIRSTLINEDISPLAY)
		LoadWord
		rcall	LCD_Putstring
;		Secondline
;		ldi		arg,'>'
;		rcall 	lcd_putc
;		movw	Zh:Zl,Xh:Xl
;		MoveZTo (SECONDLINEDISPLAY)
;		LoadWord
;		rcall	LCD_Putstring	
		ret

