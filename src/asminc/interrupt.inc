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
;	INTERRUPT
;******************************************************************
; Implementación de la funcionalidad correspondiente al botón
; de interrupción.
;******************************************************************

;*****************************************************************
; CONSTANTES
;*****************************************************************

        .equ    INT_PORT        =       PORTD
        .equ    INT_DDR         =       DDRD
        .equ    INT_BTN         =       3 ; Pin correspondiente al boton de interrupción externa (corresponde a PD2)

;*****************************************************************
; interrupt_init: Inicializa la configuración de las interrupciones
; de manera tal que cuando se aprieta el boton de interrupción
; se vuelve al menu principal.
;*****************************************************************

interrupt_init:
        sbi     INT_DDR, INT_BTN        ; INT_DDR.INT_BTN es salida
        sbi     INT_PORT, 0b00000010    ; Activo pull-up
        ldi     tmp, 1<<INT0            ; Seteo INT0
        ;; out     GICR, tmp               ; Cargo esta opción en el GICR
        ;; ldi     tmp, 0b00000010         ; Seteo que la interrupción ocurra cuando hay un flanco descendente
        out     MCUCR, tmp              ; Cargo esta opción en el MCUCR
        sei                             ; Habilito interrupciones en forma global
