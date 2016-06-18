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
;       MATLAB
;******************************************************************
; Rutinas utilizadas para definir cómo se realiza la comunicación
; con matlab a la hora de ir pasando muestras de una función.
;******************************************************************

;******************************************************************
; CONSTANTES
;******************************************************************

.equ channel = 0  ;; ADC0

;******************************************************************
; intensity_init: Inicializa el ADC.
;******************************************************************

intensity_init:
        ldi     tmp, (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0)
        out     ADCSR, tmp
        ; ADEN  es ADC enable
        ; ADPSx es prescaler
        ; ADSC  es empezar conversion

        ldi     tmp, (1<<REFS0) ;referencia = AVCC (=VCC)
        out     ADMUX, tmp
        ; REFS1:REFS0 - reference voltage (segun micro)
        ; MUX2:MUX0   - channel select
        ret


;******************************************************************
; intensity_loop: Rutina que va leyendo indefinidamente el
; valor analógico de tensión que se encuentra en el pin ADC_PIN
; y lo tranforma en un valor digital. Luego se muestra el valor
; medido en el display.
;******************************************************************

intensity_loop:
        rcall   wait5ms
        rcall   wait5ms

        ldi     tmp, 0b11110000
        out     DDRA, tmp

        ; Leer ADC
        ldi     tmp, (1<<REFS0) | channel ; Seteo channel
        out     ADMUX, tmp
        sbi     ADCSRA, ADSC              ; Empiezo conversion

        SetLCDClearAtHome

wait_for_conv_finished:
        sbic    ADCSRA, ADSC  ; El bit ADSC se pone en bajo luego de terminar la conversion
        rjmp    wait_for_conv_finished

        in      rBin1L, ADCL
        in      rBin1H, ADCH

        ldi     tmp, 0x12
        ldi     tmp2, 0x03
        ;; mov     rBin1L, tmp
        ;; mov     rBin1H, tmp2

        ;; SetLcdClearAtHome
        ;; rcall   Bin2ToAsc
        ;; ;; ldi 	zh, high(strTst << 1)
	;; ;; ldi 	zl, low(strTst << 1)
        ;; rcall   lcd_putstring

	movw	rBin1H:rBin1L, tmp2:tmp
	ldi     Zh, high(buffer)
	ldi 	Zl, low(buffer)
	rcall	Bin2ToAsc5
	ldi     tmp, 5
	ld	arg, Z+
tsloop10:
        LcdPutChar
	ld	arg, Z+
	dec     tmp
	cpi     tmp, 0
	brne    tsloop10

        rjmp    intensity_loop
