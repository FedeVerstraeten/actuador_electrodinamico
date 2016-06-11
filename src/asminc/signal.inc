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
        .equ    SIGNAL_DDR      =       DDRB
        .equ    SIGNAL_PORT     =       PORTB

        .equ    SIGNAL_NUMSPL   =       0x50 ; Numero de muestras de las funciones precargadas

        .equ    ENDSIG          =       0xCB

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
; signal_out_sawt: Recorre las muestras precargadas en memoria ROM
; correspondientes a una dientes de sierra y las va enviando
; hacia el DAC.
;******************************************************************

signal_out_sawt:
        ldi     Zh, high(samplesSawt<<1)
        ldi     Zl, low(samplesSawt<<1)
        lpm     tmp, Z+

sawt_loop:
        lpm     tmp2, Z+
        CheckSignalEnd sawt_loop_continue, signal_out_sawt
sawt_loop_continue:
        out     SIGNAL_PORT, tmp
        mov     tmp, tmp2
        rjmp    sawt_loop
