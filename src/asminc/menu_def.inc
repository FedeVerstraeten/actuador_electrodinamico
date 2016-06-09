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
;	MENU_DEF
;******************************************************************
;
; Información almacenada en Program Memory (ROM).
;
; Definición de los elementos del menú:
;	- Mensajes del menú a imprimirse en el Display
;	- Listado de instrucciones según funcionalidad (handler)
;	- Variables y constantes.
;
; Se define una "Tabla de Opciones (OPTIONS_TABLE)".
; Por cada opción del menú, existe una sentencia con el siguiente
; formato:
;
; OPTION:	previous(0-1),
;		next(2-3),
;		enter(4-5),
;		firstLineHandler(6-7),
;		secondLineHandler(8-9),
;		firstline(10-11),
;		secondline(12-13)
;
; Por cada componente de OPTION se cargan las partes High y Low de
; la dirección de memoria de la sentencia que se ejecuta.
;******************************************************************


;*****************************************************************
;	CONSTANTES
;*****************************************************************

; Botones controladores
	.equ	SWITCHUP	= 	2
	.equ	SWITCHDW	= 	3
	.equ	SWITCHEN	= 	4

; Cadenas de caracteres
	.equ	ENDSTR	        =	0		; Fin del String
	.equ	PREV	        =	0
	.equ	NEXT	        =	2
	.equ	ENTER	        =	4
	.equ 	FIRSTLINEHANDLER	=	6
	.equ 	SECONDLINEHANDLER	=	8
	.equ 	FIRSTLINEDISPLAY	=	10
	.equ 	SECONDLINEDISPLAY	=	12

;*****************************************************************
;	OPTIONS_TABLE:
;	Definicion OPTION. Secuencia de cadenas de caracteres en ROM.
;*****************************************************************

.cseg
	.org 0x0600

	Matlab: .db		high(checkButtons),low(checkButtons),high(optSeno),low(optSeno),high(commMatlab),low(commMatlab),high(fstLineStrDisplay),low(fstLineStrDisplay),high(sndLineStrDisplay),low(sndLineStrDisplay),high(strMatlab<<1),low(strMatlab<<1),high(strSeno<<1),low(strSeno<<1)

	Seno: .db		high(optMatlab),low(optMatlab),high(optCuadrada),low(optCuadrada),high(genSeno),low(genSeno),high(fstLineStrDisplay),low(fstLineStrDisplay),high(sndLineStrDisplay),low(sndLineStrDisplay),high(strSeno<<1),low(strSeno<<1),high(strCuadrada<<1),low(strCuadrada<<1)

	Cuadrada: .db		high(optSeno),low(optSeno),high(optSierra),low(optSierra),high(genCuadrada),low(genCuadrada),high(fstLineStrDisplay),low(fstLineStrDisplay),high(sndLineStrDisplay),low(sndLineStrDisplay),high(strCuadrada<<1),low(strCuadrada<<1),high(strSierra<<1),low(strSierra<<1)

	Sierra:	.db		high(optCuadrada),low(optCuadrada),high(optIntensidad),low(optIntensidad),high(genSierra),low(genSierra),high(fstLineStrDisplay),low(fstLineStrDisplay),high(sndLineStrDisplay),low(sndLineStrDisplay),high(strSierra<<1),low(strSierra<<1),high(strIntensidad<<1),low(strIntensidad<<1)

	Intensidad: .db		high(optSierra),low(optSierra),high(optMatlab),low(optMatlab),high(medInten),low(medInten),high(fstLineStrDisplay),low(fstLineStrDisplay),high(sndLineStrDisplay),low(sndLineStrDisplay),high(strIntensidad<<1),low(strIntensidad<<1),high(strMatlab<<1),low(strMatlab<<1)

; Mensajes por display

	strMatlab:	.db 	"Matlab",ENDSTR
	strSeno:	.db 	"Seno",ENDSTR
	strCuadrada:	.db	"Cuadrada",ENDSTR
	strSierra:	.db	"Diente sierra",ENDSTR
	strIntensidad:	.db	"Medir intensidad",ENDSTR

