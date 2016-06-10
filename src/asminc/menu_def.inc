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
; CONSTANTES
;*****************************************************************

; DDR correspondiente a los botones controladores
        .equ    MENU_DDR        =       DDRC

; Puerto correspondiente a los botones controladores
        .equ    MENU_PORT       =       PORTC

; Pin correspondiente a los botones controladores
        .equ    MENU_PIN        =       PINC

; Pines correspondientes a los botones controladores
	.equ	SWITCHUP	= 	2
	.equ	SWITCHDW	= 	3
	.equ	SWITCHEN	= 	4

; Cadenas de caracteres
	.equ	ENDSTR	        =	0		; Fin del String
	.equ	PREV	        =	0
	.equ	NEXT	        =	2
	.equ	ENTER	        =	4
	.equ 	FSTLINEHANDLER	=	6
	.equ 	SNDLINEHANDLER	=	8
	.equ 	FSTLINESTR	=	10
	.equ 	SNDLINESTR	=	12

;*****************************************************************
; OPTIONS_TABLE:
; Definicion OPTION. Secuencia de cadenas de caracteres en ROM.
;*****************************************************************

.cseg
	.org 0x0600

	Matlab: .db		high(check_buttons),low(check_buttons),high(opt_seno),low(opt_seno),high(comm_matlab),low(comm_matlab),high(fst_line_str_display),low(fst_line_str_display),high(snd_line_str_display),low(snd_line_str_display),high(strMatlab<<1),low(strMatlab<<1),high(strSeno<<1),low(strSeno<<1)

	Seno: .db		high(opt_matlab),low(opt_matlab),high(opt_cuadrada),low(opt_cuadrada),high(gen_seno),low(gen_seno),high(fst_line_str_display),low(fst_line_str_display),high(snd_line_str_display),low(snd_line_str_display),high(strSeno<<1),low(strSeno<<1),high(strCuadrada<<1),low(strCuadrada<<1)

	Cuadrada: .db		high(opt_seno),low(opt_seno),high(opt_sierra),low(opt_sierra),high(gen_cuadrada),low(gen_cuadrada),high(fst_line_str_display),low(fst_line_str_display),high(snd_line_str_display),low(snd_line_str_display),high(strCuadrada<<1),low(strCuadrada<<1),high(strSierra<<1),low(strSierra<<1)

	Sierra:	.db		high(opt_cuadrada),low(opt_cuadrada),high(opt_intensidad),low(opt_intensidad),high(gen_sierra),low(gen_sierra),high(fst_line_str_display),low(fst_line_str_display),high(snd_line_str_display),low(snd_line_str_display),high(strSierra<<1),low(strSierra<<1),high(strIntensidad<<1),low(strIntensidad<<1)

	Intensidad: .db		high(opt_sierra),low(opt_sierra),high(opt_matlab),low(opt_matlab),high(medInten),low(medInten),high(fst_line_str_display),low(fst_line_str_display),high(snd_line_str_display),low(snd_line_str_display),high(strIntensidad<<1),low(strIntensidad<<1),high(strMatlab<<1),low(strMatlab<<1)

; Lista de mensajes que se muestran por display

	strMatlab:	.db 	"Matlab",ENDSTR
	strSeno:	.db 	"Seno",ENDSTR
	strCuadrada:	.db	"Cuadrada",ENDSTR
	strSierra:	.db	"Diente sierra",ENDSTR
	strIntensidad:	.db	"Medir intensidad",ENDSTR

