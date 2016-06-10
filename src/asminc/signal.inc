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

        .equ    ENDSIG          =       0xCB

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
; signal_out: Recorre las muestras almacenadas en memoria
; correspondientes a una señal periódica y las va enviando
; hacia el DAC.
;******************************************************************

