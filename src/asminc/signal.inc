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
;       SIGNAL
;******************************************************************
; Rutinas utilizadas para enviar las muestras de una función
; hacia el DAC.
;******************************************************************

;******************************************************************
; CONSTANTES
;******************************************************************
        .equ    SIGNAL_DDR      =       DDRC
        
		.equ    SIGNAL_PORT     =       PORTC

        .equ    SIGNAL_NUMSPL   =       0x50 ; Numero de muestras de las funciones precargadas

        .equ    ENDSIG          =       0xCB
		
		.equ maxAmp = 127 ; Amplitud Maxima

		.equ delay = 255 ; Delay, si aumenta el delay tendriamos frecuencias mas bajas
		
;******************************************************************
; SIGNAL_TABLE: Diferentes muestras que componen a un período
; de un seno y una dientes de sierra. Se almacenan en memoria
; ROM del micro y se obtiene su posición calculando hasta que
; punto de la ROM ocupa el programa en si y grabando las
; muestras luego de dicho punto.
;******************************************************************


;******************************************************************
; signal_init: Inicializa como salida los DDR de los pines en los
; que esta conectado el DAC.
;******************************************************************

signal_init:
        in      tmp, SIGNAL_DDR
        sbr     tmp, 0b11111111
        out     SIGNAL_DDR, tmp
        ret

;******************************************************************
; signal_out_matlab: Recorre las muestras almacenadas en memoria
; RAM correspondientes a una señal periódica armada en matlab
; y las va enviando hacia el DAC.
;******************************************************************

signal_out_matlab:
        ldi     Zh, high(SRAM_START)
        ldi     Zl, low(SRAM_START)
        ld      tmp, Z+
matlab_loop:
        ld      tmp2, Z+
        ;; rcall   signal_check_end_sample
        CheckSignalEnd matlab_loop_continue, signal_out_matlab
matlab_loop_continue:
        out     SIGNAL_PORT, tmp
        mov     tmp, tmp2
        rjmp    matlab_loop

;******************************************************************
; signal_out_sine: Recorre las muestras precargadas en memoria ROM
; correspondientes a un seno y las va enviando hacia el DAC.
;******************************************************************

signal_out_sine:
        ldi     Zh, high(samplesSin<<1)
        ldi     Zl, low(samplesSin<<1)
        lpm     tmp, Z+

sine_loop:
        lpm     tmp2, Z+
        CheckSignalEnd sine_loop_continue, signal_out_sine
sine_loop_continue:
        out     SIGNAL_PORT, tmp
        mov     tmp, tmp2
        rjmp    sine_loop

;******************************************************************
; signal_out_sawt: Genera una funcion diente de sierra
; y va enviando las muestras hacia el DAC.
;******************************************************************
signal_out_sawt:
        ldi     tmp, 0xFF
sawt_loop:
        inc     tmp                     ; tmp = 0->1->...->256->0->...
        out     SIGNAL_PORT, tmp
        nop                             ; Para que se "recupere" el DAC
        nop
        rjmp    sawt_loop
		
;******************************************************************
; signal_out_square: Genera una funcion cuadrada
; y va enviando las muestras hacia el DAC.
;******************************************************************

signal_out_square:
	ldi tmp,0xFF
	out SIGNAL_DDR,tmp
square_loop:
	clr tmp		;limpio tmp para usarlo
loop_high:
	ldi tmp,0xFF
	out SIGNAL_PORT,tmp 
	ldi tmp2,delay
delay_high:	
	dec tmp2
	brne delay_high		;Si tmp es distinto de cero vuelve a hacer delay
	cpi tmp,maxAmp		;comparo con maxAmp
	BRCS loop_high			;si se setea el carry sigo en este loop
loop_low:
	ldi tmp,0
	out SIGNAL_PORT,tmp
	ldi tmp2,delay
delay_low:

	dec tmp2
	brne delay_low		;Si rmp es distinto de cero vuelve a hacer delay
	brne loop_low		;si se setea el carry sigo en este loop
	rjmp signal_out_square		;termina y vuelve a empezar

;******************************************************************
; signal_out_triangle: Genera una funcion triangular
; y va enviando las muestras hacia el DAC.
;******************************************************************

signal_out_triangle:
	ldi tmp,0xFF 
	out SIGNAL_DDR,tmp
triangle_loop:
	clr tmp		;limpio tmp para usarlo
loop_up:
	out SIGNAL_PORT,tmp 
	ldi tmp2,delay
delay_up:	
	dec tmp2
	brne delay_up		;Si tmp es distinto de cero vuelve a hacer delay
	inc tmp				; incremento tmp
	cpi tmp,maxAmp		;comparo con maxAmp
	brcs loop_up			;si se setea el carry sigo en este loop
loop_down:
	out SIGNAL_PORT,tmp
	ldi tmp2,delay
delay_down:

	dec tmp2
	brne delay_down		;Si rmp es distinto de cero vuelve a hacer delay
	dec tmp				;disminuyo tmp
	brne loop_down		;si se setea el carry sigo en este loop
	RJMP signal_out_triangle		;termina y vuelve a empezar
	
;******************************************************************
; signal_out_sawt: Recorre las muestras precargadas en memoria ROM
; correspondientes a una dientes de sierra y las va enviando
; hacia el DAC.
;******************************************************************

;; signal_out_sawt:
;;         ldi     Zh, high(samplesSawt<<1)
;;         ldi     Zl, low(samplesSawt<<1)
;;         lpm     tmp, Z+

;; sawt_loop:
;;         lpm     tmp2, Z+
;;         CheckSignalEnd sawt_loop_continue, signal_out_sawt
;; sawt_loop_continue:
;;         out     SIGNAL_PORT, tmp
;;         mov     tmp, tmp2
;;         rjmp    sawt_loop
