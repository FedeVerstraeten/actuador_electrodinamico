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
;
; Implementación rutinas y subrutinas ejectutadas en la interacción
; con el menú.
;******************************************************************

showScreen:
		SetLcdClearAtHome
		movw	Zh:Zl,Xh:Xl
		MoveZTo (firstHandler)
		rcall	jumper
		movw	Zh:Zl,Xh:Xl
		MoveZTo (secondHandler)
		rcall   jumper
		rjmp	checkButtons
		
checkButtons:
		;reseteo las flags de las keys
	;	rcall delay200ms
		
		;Lectura BUTTONS por Puerto C
		in		tmp,PINC
		
		;El bit del boton presionado estará en cero
		sbrs	tmp,switchUP
		rjmp	pressUP
		sbrs	tmp,switchDW
		rjmp	pressDOWN
		sbrs	tmp,switchRT
		rjmp	pressRET
	
		;Nueva lectura por si los botones no se presionaron
		;luego de esperar por posibles rebotes
		rjmp	checkButtons
		
jumper:
		LoadWord
		ijmp

PressUp:
		movw	Zh:Zl,Xh:Xl
		rjmp	jumper
		
PressDown:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(next)
		rjmp	jumper
		
PressRet:
		movw	Zh:Zl,Xh:Xl
		MoveZTo	(fwd)
		rjmp	jumper
