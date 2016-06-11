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

Matlab: .db high(check_buttons),low(check_buttons),high(opt_sin),low(opt_sin),high(comm_start),low(comm_start),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strMatlab<<1),low(strMatlab<<1),high(strSin<<1),low(strSin<<1)

Sine: .db high(opt_matlab),low(opt_matlab),high(opt_square),low(opt_square),high(gen_sin),low(gen_sin),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSin<<1),low(strSin<<1),high(strSquare<<1),low(strSquare<<1)

Square: .db high(opt_sin),low(opt_sin),high(opt_sawt),low(opt_sawt),high(gen_square),low(gen_square),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSquare<<1),low(strSquare<<1),high(strSawt<<1),low(strSawt<<1)

Sawtooth:.db high(opt_square),low(opt_square),high(opt_intnsty),low(opt_intnsty),high(gen_sawt),low(gen_sawt),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strSawt<<1),low(strSawt<<1),high(strIntnsty<<1),low(strIntnsty<<1)

Intnsty: .db high(opt_sawt),low(opt_sawt),high(opt_matlab),low(opt_matlab),high(med_intnsty),low(med_intnsty),high(fstline_dsp),low(fstline_dsp),high(sndline_dsp),low(sndline_dsp),high(strIntnsty<<1),low(strIntnsty<<1),high(strMatlab<<1),low(strMatlab<<1)

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

strCommIdle:    .db     "Esperando handshake",ENDSTR
strCommStore:   .db     "Guardando muestras",ENDSTR,ENDSTR

strSignalOut:   .db     "Enviando senal",ENDSTR,ENDSTR

; Lista de funciones precargadas en memoria
; (tal vez convendría ponerlas en un archivo aparte pero no se cómo
; se maneja el tema de la posición en la memoria del programa).
samplesSin: .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
samplesSawt:.dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
            .dB 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A
