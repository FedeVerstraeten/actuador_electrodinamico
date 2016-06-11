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
;	DELAY
;******************************************************************
; Rutinas para generar un retardo temporal.
;******************************************************************

;******************************************************************
; delay_1s: Rutina de delay.
;******************************************************************

delay_1s:
	rcall   delay_200ms
	rcall   delay_200ms
	rcall   delay_200ms
	rcall   delay_200ms
	rcall   delay_200ms
	ret

;******************************************************************
; delay_200ms: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

delay_200ms:
        push    tmp
        push    tmp2
	ldi	tmp, 10
delay200ms_outer:
	ldi	tmp2, 100
delay200ms_inner:
        rcall   delay_1ms
	dec     tmp2
	brne    delay200ms_inner
	dec	tmp
	brne    delay200ms_outer
        pop     tmp2
        pop     tmp
	ret


;******************************************************************
; delay_1ms: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

delay_1ms:
        push    tmp
        push    tmp2
        ldi     tmp, 10
delay_1ms_outer:
        ldi     tmp2, 100
delay_1ms_inner:
        rcall   delay_1us
        dec     tmp2                    ; 1 ciclo
        brne    delay_1ms_inner         ; 1 ciclo
        dec     tmp                     ; Cada vez que llega aca pasaron ~100us
        brne    delay_1ms_outer
        pop     tmp2
        pop     tmp
        ret

;******************************************************************
; delay_1us: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

delay_1us:
        push    tmp
        push    tmp2
        ldi     tmp, 10
delay_1us_outer:
        clr     tmp2
delay_1us_inner:
        dec     tmp2                    ; 1 ciclo
        brne    delay_1us_inner         ; 1 ciclo
        dec     tmp                     ; Cada vez que llega aca pasaron ~100ns
        brne    delay_1us_outer
        pop     tmp2
        pop     tmp
        ret

