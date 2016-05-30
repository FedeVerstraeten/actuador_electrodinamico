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
;	MENU_DEF
;******************************************************************
;
; Información almacenada en Program Memory (ROM).
;
; Definición de de elementos del menú:
;	- Mensajes del menú a imprimirse en el Display
;	- Listado de instrucciones según funcionalidad (handler)
;	- Variables y constantes.
;
; Se define una "Tabla de Opciones (OPTIONS TABLE)".
; Por cada opción del menú, existe una sentencia con el siguiente 
; formato:
;	
; OPTION:	previous(1),previous(2)
;			next(1),next(2)
;			enter(2),enter(2),
;			firstLineHandler,secondLineHandler,
;			firstline,secondline
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
	.equ	ENDSTR	=	0		; Fin del String
	.equ	PREV	=	0
	.equ	NEXT	=	2
	.equ	ENTER	=	4
	.equ 	FIRSTLINEHANDLER	=	6
	.equ 	SECONCDLINEHANDLER	=	8
	.equ 	FIRSTLINEDISPLAY	=	10
	.equ 	SECONDLINEDISPLAY	=	12

;*****************************************************************
;	OPTIONS TABLE:
;	Definicion OPTION. Secuencia de cadenas de caracteres en ROM.
;*****************************************************************
   
.cseg
	.org 0x0600   
	
	Matlab:	.db		high(check_keys),low(check_keys),high(lSeno),low(lSeno),high(genSeno),low(genSeno),high(flstd),low(flstd),high(slstd),low(slstd),high(strMatlab<<1),low(strMatlab<<1),high(strSeno<<1),low(strSeno<<1)
	
	

; Cadenas de caractateres en Display
	 
	strMatlab:	.db 	"Matlab",ENDSTR
	strSeno:	.db 	"Seno",ENDSTR
	
