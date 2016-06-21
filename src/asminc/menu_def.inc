;******************************************************************
; Materia......: Laboratorio de Microprocesadores.
; Curso........: Campigglio - Stola
; Fecha inicio.: 14/03/2016
; Fecha entrega: 21/06/2016
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
        .equ    MENU_DDR        =       DDRD

; Puerto correspondiente a los botones controladores
        .equ    MENU_PORT       =       PORTD

; Pin correspondiente a los botones controladores
        .equ    MENU_PIN        =       PIND

; Pines correspondientes a los botones controladores
	.equ	SWITCHDW	= 	3
        .equ	SWITCHUP	= 	4
	.equ	SWITCHEN	= 	5

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

Matlab: .db high(opt_intnsty),low(opt_intnsty),high(opt_sin),low(opt_sin),high(gen_matlab),low(gen_matlab),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strMatlab<<1),low(strMatlab<<1),high(strSin<<1),low(strSin<<1)

Sine: .db high(opt_matlab),low(opt_matlab),high(opt_square),low(opt_square),high(gen_sin),low(gen_sin),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSin<<1),low(strSin<<1),high(strSquare<<1),low(strSquare<<1)

Square: .db high(opt_sin),low(opt_sin),high(opt_sawt),low(opt_sawt),high(gen_square),low(gen_square),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSquare<<1),low(strSquare<<1),high(strSawt<<1),low(strSawt<<1)

Sawtooth:.db high(opt_square),low(opt_square),high(opt_tri),low(opt_tri),high(gen_sawt),low(gen_sawt),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSawt<<1),low(strSawt<<1),high(strTri<<1),low(strTri<<1)

Triangle:.db high(opt_sawt),low(opt_sawt),high(opt_intnsty),low(opt_intnsty),high(gen_tri),low(gen_tri),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strTri<<1),low(strTri<<1),high(strIntnsty<<1),low(strIntnsty<<1)

Intnsty: .db high(opt_tri),low(opt_tri),high(opt_matlab),low(opt_matlab),high(med_intnsty),low(med_intnsty),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strIntnsty<<1),low(strIntnsty<<1),high(strMatlab<<1),low(strMatlab<<1)

; Lista de mensajes que se muestran por display
; Algunos tienen doble ENDSTR, esto es porque la memoria
; del programa es de 16 Bytes y algunos strings tienen un
; número par de bytes, con lo cual al agregar el byte del
; ENDSTR queda 1 byte extra por llenar a la hora de guardar
; la memoria ROM y en esos casos el compilador tira warnings.

strMatlab:	.db 	"Matlab",ENDSTR,ENDSTR
strSin:	        .db 	"Seno",ENDSTR,ENDSTR
strSquare:	.db	"Cuadrada",ENDSTR,ENDSTR
strSawt:	.db	"Diente sierra",ENDSTR
strIntnsty:	.db	"Medir intensidad",ENDSTR,ENDSTR
strTri:         .db	"Triangular",ENDSTR,ENDSTR

strIntnstyMed:  .db	"Intensidad:",ENDSTR

strCommIdle:    .db     "Espera handshake",ENDSTR,ENDSTR
strCommStore:   .db     "Guardar muestras",ENDSTR,ENDSTR

strSignalOut:   .db     "Enviando senal",ENDSTR,ENDSTR

strWelcome:	.db	"**Bienvenidos**",ENDSTR
strGlomae:	.db	"**GLOmAe 2016**",ENDSTR

; Lista de funciones precargadas en memoria
; (tal vez convendría ponerlas en un archivo aparte pero no se cómo
; se maneja el tema de la posición en la memoria del programa).
samplesSin: .db 0,0,0,0,0,0,0,1,1,2,3,3,4,5,6,7,8,9,10,12,13,15,16,18,19,21,23,25,27,29
	    .db 31,33,35,37,39,42,44,46,49,51,54,56,59,62,64,67,70,73,76,79,81,84,87,90
	    .db 93,96,99,103,106,109,112,115,118,121,124,128,131,134,137,140,143,146,149,152,156,159,162,165
	    .db 168,171,174,176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,218,220,222,224,226,228,230
	    .db 232,234,236,237,239,240,242,243,245,246,247,248,249,250,251,252
        .db 252,253,254,254,255,255,255,255,255,255,255,255,255,255,255,254,254,253,252,252,251,250,249,248
	    .db 247,246,245,243,242,240,239,237,236,234,232,230,228,226,224,222,220,218,216,213,211,209,206,204
	    .db 201,199,196,193,191,188,185,182,179,176,174,171,168,165,162,159,156,152,149,146,143,140,137,134,131,128
	    .db 124,121,118,115,112,109,106,103,99,96,93,90,87,84,81,79,76,73,70,67,64,62,59,56,54,51
	    .db 49,46,44,42,39,37,35,33,31,29,27,25,23,21,19,18,16,15,13,12,10,9,8,7,6,5,4,3
	    .db 2,1,1,0,0,0,ENDSIG,ENDSIG
