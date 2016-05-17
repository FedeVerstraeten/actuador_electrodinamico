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
;	- Mensajes a imprimirse en el menú
;	- Listado de instrucciones según funcionalidad (handler)
;	- Variables y constantes.
;
; Por cada opción existente del menú existe una sentencia con el 
; siguiente formato:
;	
; OPTION:	prev(2),
;			next(2),
;			return(2),
;			firsthandler,secondhandler,
;			firstline,secondline
;
; Por cada componente de OPTION se cargan las partes High y Low de
; la dirección de memoria de la sentencia que se ejecuta.
;******************************************************************


;*****************************************************************
;	Constantes
;*****************************************************************
	

; Botones controladores
	.equ	switchUP	= 	2
	.equ	switchDW	= 	3
	.equ	switchRT	= 	4
	
;-Cadenas de caracteres
	.equ	ENDSTR		=	0		; Fin del String
	.equ	PREV		=	0
	.equ	NEXT		=	2
	.equ	fwd			=	4
	.equ 	FIRSTHANDLER	=	6
	.equ 	SECONDHANDLER	=	8
	.equ 	fstline = 10
	.equ 	scdline = 12

;*****************************************************************
;	Definicion OPTION. Secuencia de cadenas de caracteres en ROM
;*****************************************************************
   
.cseg
	.org 0x0600   
	
	Lectura:	.db		high(checkButtons),low(checkButtons),high(lCalibra),low(lCalibra),high(ComunicateL),low(ComunicateL),high(flstd),low(flstd),high(slstd),low(slstd),high(strLectura<<1),low(strLectura<<1),high(sCalibra<<1),low(sCalibra<<1)
		strLectura:	.db 	"Lectura",ENDSTR
	
