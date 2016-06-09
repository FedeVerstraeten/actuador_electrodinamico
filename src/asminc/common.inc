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
;	Rutinas comunes para todas las tareas
;******************************************************************

;******************************************************************
; Delay_1s: Rutina de delay.
;******************************************************************

Delay_1s:
	rcall   Delay_200ms
	rcall   Delay_200ms
	rcall   Delay_200ms
	rcall   Delay_200ms
	rcall   Delay_200ms
	ret

;******************************************************************
; Delay_200ms: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

Delay_200ms:
	ldi	tmp, 10
delay200ms_outer:
	ldi	tmp2, 100
delay200ms_inner:
        Delay_1ms
	dec     tmp2
	brne    delay200ms_inner
	dec	tmp
	brne    delay200ms_outer
	ret


;******************************************************************
; Delay_1ms: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

Delay_1ms:
        push    tmp
        push    tmp2
        ldi     tmp, 10
delay_1ms_outer:
        ldi     tm2, 100
delay_1ms_inner:
        Delay_1us
        dec     tmp2                    ; 1 ciclo
        brne    delay_1ms_inner         ; 1 ciclo
        dec     tmp                     ; Cada vez que llega aca pasaron ~100us
        brne    delay_1ms_outer
        pop     tmp
        pop     tmp2

;******************************************************************
; Delay_1us: Rutina de delay.
; Considera la presencia de un clock de 16 MHz
;******************************************************************

Delay_1us:
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
        pop     tmp
        pop     tmp2

